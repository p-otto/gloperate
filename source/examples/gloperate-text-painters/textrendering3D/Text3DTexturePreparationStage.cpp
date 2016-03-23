
#include "Text3DTexturePreparationStage.h"

#include <glbinding/gl/gl.h>

#include <globjects/Framebuffer.h>
#include <globjects/Texture.h>
#include <globjects/Program.h>

#include <gloperate/gloperate.h>
#include <gloperate/base/make_unique.hpp>
#include <gloperate/primitives/PolygonalDrawable.h>
#include <gloperate/primitives/Scene.h>
#include <gloperate/primitives/PolygonalGeometry.h>
#include <gloperate-text/Typesetter.h>
#include <gloperate-text/FontFace.h>

using gloperate::make_unique;

using namespace gl;
using gl::GLenum;

Text3DTexturePreparationStage::Text3DTexturePreparationStage()
{
    addInput("sequences", sequences);
    addInput("font", font);

    addOutput("textures", textures);
}

Text3DTexturePreparationStage::~Text3DTexturePreparationStage()
{
}

void Text3DTexturePreparationStage::initialize()
{
    m_renderer = make_unique<gloperate_text::GlyphRenderer>();

    m_program = new globjects::Program();
    m_program->attach(
        globjects::Shader::fromFile(GL_VERTEX_SHADER, gloperate::dataPath() + "/gloperate-text/shaders/glyph.vert"),
        globjects::Shader::fromFile(GL_GEOMETRY_SHADER, gloperate::dataPath() + "/gloperate-text/shaders/glyph.geom"),
        globjects::Shader::fromFile(GL_FRAGMENT_SHADER, gloperate::dataPath() + "/gloperate-text/shaders/copy.frag")
    );

    alwaysProcess(true);
}

void Text3DTexturePreparationStage::process()
{
    glDisable(GLenum::GL_DEPTH_TEST);

    textures->clear();

    m_program->use();
    m_program->setUniform("glyphs", 0);

    glViewport(0, 0, 512, 512);

    for (auto& sequence : sequences.data())
    {
        globjects::ref_ptr<globjects::Framebuffer> fbo = new globjects::Framebuffer;
        globjects::ref_ptr<globjects::Texture> tex = globjects::Texture::createDefault(GL_TEXTURE_2D);
        tex->image2D(0, GL_R8, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

        fbo->attachTexture(GLenum::GL_COLOR_ATTACHMENT0, tex);
        fbo->printStatus(true);

        fbo->bind();
        fbo->setDrawBuffer(GLenum::GL_COLOR_ATTACHMENT0);
        fbo->clearBuffer(GL_COLOR, 0, glm::vec4(0.0, 0.0, 0.0, 1.0));

        gloperate_text::GlyphVertexCloud cloud{};
        cloud.vertices().resize(sequence.size(*font.data()));

        auto extent = gloperate_text::Typesetter::typeset(sequence, *font.data(), cloud.vertices().begin());
        cloud.update();
        cloud.setTexture(font.data()->glyphTexture());
    
        cloud.texture()->bindActive(0);
        cloud.drawable()->draw();

        textures->push_back(tex);
    }
    m_program->release();

    invalidateOutputs();
}
