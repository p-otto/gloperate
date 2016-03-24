
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
    addInput("textures", textures);
    addInput("viewport", viewport);
    addInput("camera", camera);
    addInput("projection", projection);

    addOutput("color", color);
    addOutput("normal", normal);
    addOutput("depth", depth);

    alwaysProcess(true);
}

Text3DRenderStage::~Text3DRenderStage()
{
}

void Text3DRenderStage::initialize()
{
    glEnable(GLenum::GL_BLEND);
    glBlendFunc(GLenum::GL_SRC_ALPHA, GLenum::GL_ONE_MINUS_SRC_ALPHA);

    auto geometry = resourceManager.data()->load<gloperate::Scene>("datasets/CornellBox-Original_skinned.obj");

    for(auto& mesh : geometry->meshes())
    {
        m_drawables.emplace_back(gloperate::PolygonalDrawable(*mesh));
    }

    camera.data()->setCenter(glm::vec3(0.0, 1.0, 0.0));
    camera.data()->setEye(glm::vec3(0.0, 1.0, 4.0));

    m_program = new globjects::Program();
    m_program->attach(
        globjects::Shader::fromFile(GL_VERTEX_SHADER, "data/gloperate-text/shaders/plain.vert"),
        globjects::Shader::fromFile(GL_FRAGMENT_SHADER, "data/gloperate-text/shaders/plain.frag")
    );

    color.data() = globjects::Texture::createDefault(GL_TEXTURE_2D);
    normal.data() = globjects::Texture::createDefault(GL_TEXTURE_2D);
    depth.data() = globjects::Texture::createDefault(GL_TEXTURE_2D);

    m_fbo = new globjects::Framebuffer;
    m_fbo->attachTexture(GL_COLOR_ATTACHMENT0, color.data());
    m_fbo->attachTexture(GL_COLOR_ATTACHMENT1, normal.data());
    m_fbo->attachTexture(GL_DEPTH_ATTACHMENT, depth.data());
}

void Text3DRenderStage::process()
{
    if (viewport.hasChanged())
    {
        resizeTexture();
    }

    glEnable(GLenum::GL_DEPTH_TEST);
    glBlendEquation(GL_FUNC_ADD);
    glViewport(viewport.data()->x(), viewport.data()->y(), viewport.data()->width(), viewport.data()->height());

    m_fbo->bind();
    m_fbo->setDrawBuffers({
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1
    });

    m_fbo->clearBuffer(GL_COLOR, 0, glm::vec4(1.0f));
    m_fbo->clearBuffer(GL_COLOR, 1, glm::vec4(0.0f));
    m_fbo->clearBufferfi(GLenum::GL_DEPTH_STENCIL, 0, 1.0f, 0);

    m_program->use();

    m_program->setUniform("modelViewProjection", projection.data()->projection() * camera.data()->view());
    m_program->setUniform("glyphTexture", 0);
    m_program->setUniform("opaqueWalls", static_cast<int>(opaque.data()));

    int count = 0;
    for (auto& drawable : m_drawables)
    {
        textures->at(count)->bindActive(0);
        drawable.draw();
        if(++count >= textures->size())
        {
            --count;
        }
    }

    m_program->release();

    m_fbo->unbind();
}

void Text3DRenderStage::resizeTexture()
{
    auto size = glm::ivec2{
        viewport.data()->width(), viewport.data()->height()
    };

    color.data()->image2D(0, GL_RGB8, size, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    normal.data()->image2D(0, GL_RGB32F, size, 0, GL_RGB, GL_FLOAT, nullptr);
    depth.data()->image2D(0, GL_DEPTH_COMPONENT, size, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    m_fbo->printStatus(true);
}
