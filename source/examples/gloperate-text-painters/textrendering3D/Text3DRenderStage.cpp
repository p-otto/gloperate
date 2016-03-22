
#include "Text3DRenderStage.h"

#include <glbinding/gl/gl.h>

#include <globjects/Framebuffer.h>
#include <globjects/Texture.h>

#include <gloperate/base/make_unique.hpp>
#include <gloperate/primitives/PolygonalDrawable.h>
#include <gloperate/primitives/Scene.h>
#include <gloperate/primitives/PolygonalGeometry.h>

using gloperate::make_unique;

using namespace gl;
using gl::GLenum;

Text3DRenderStage::Text3DRenderStage()
{
    addInput("resourceManager", resourceManager);
    addInput("vertexCloud", vertexCloud);
    addInput("viewport", viewport);
    addInput("targetFramebuffer", targetFramebuffer);

    alwaysProcess(true);
}

Text3DRenderStage::~Text3DRenderStage()
{
}

void Text3DRenderStage::initialize()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GLenum::GL_BLEND);
    glBlendFunc(GLenum::GL_SRC_ALPHA, GLenum::GL_ONE_MINUS_SRC_ALPHA);

    auto geometry = resourceManager.data()->load<gloperate::Scene>("datasets/CornellBox-Original2.obj");

    for(auto& mesh : geometry->meshes())
    {
        m_drawables.emplace_back(gloperate::PolygonalDrawable(*mesh));
    }

    camera.data()->setCenter(glm::vec3(0.0, 1.0, 0.0));
    camera.data()->setEye(glm::vec3(4.0, 1.0, 0.0));

    m_program = new globjects::Program();
    m_program->attach(
        globjects::Shader::fromFile(GL_VERTEX_SHADER, "data/gloperate-text/shaders/plain.vert"),
        globjects::Shader::fromFile(GL_FRAGMENT_SHADER, "data/gloperate-text/shaders/plain.frag")
    );
}

void Text3DRenderStage::process()
{
    const_cast<globjects::Texture*>(vertexCloud.data().texture())->setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    const_cast<globjects::Texture*>(vertexCloud.data().texture())->setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

    gl::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto FBO = globjects::Framebuffer::defaultFBO();

    FBO->bind();

    m_program->use();

    m_program->setUniform("modelViewProjection", projection.data()->projection() * camera.data()->view());
    m_program->setUniform("glyphTexture", 0);
    vertexCloud.data().texture()->bindActive(0);

    for (auto& drawable : m_drawables)
    {
        drawable.draw();
    }

    m_program->release();

    FBO->unbind();
}
