
#pragma once

#include <string>
#include <vector>

#include <globjects/base/ref_ptr.h>

#include <gloperate-text/GlyphVertexCloud.h>
#include <gloperate-text/GlyphRenderer.h>
#include <gloperate-text/GlyphSequence.h>
#include <gloperate/pipeline/AbstractStage.h>
#include <gloperate/pipeline/InputSlot.h>

namespace gloperate
{

    class AbstractViewportCapability;
    class PolygonalDrawable;

} // namespace gloperate


class Text3DTexturePreparationStage : public gloperate::AbstractStage
{
public:
    Text3DTexturePreparationStage();
    virtual ~Text3DTexturePreparationStage();

    virtual void initialize() override;
    virtual void process() override;

public:
    gloperate::InputSlot<std::vector<gloperate_text::GlyphSequence>> sequences;
    gloperate::InputSlot<gloperate_text::FontFace *> font;

    gloperate::Data<std::vector<globjects::ref_ptr<globjects::Texture>>> textures;

protected:
    std::unique_ptr<gloperate_text::GlyphRenderer> m_renderer;
    globjects::ref_ptr<globjects::Program> m_program;
};
