
#pragma once

#include <string>
#include <vector>

#include <glm/fwd.hpp>

#include <gloperate/pipeline/AbstractStage.h>
#include <gloperate/pipeline/Data.h>
#include <gloperate/pipeline/InputSlot.h>


namespace gloperate
{

    class AbstractViewportCapability;

} // namespace gloperate


namespace gloperate_text
{
    enum class Alignment : unsigned char;
    enum class LineAnchor : unsigned char;

    class FontFace;
    class GlyphSequence;

} // namespace gloperate_text


class Text3DGlyphSequenceStage : public gloperate::AbstractStage
{
public:
    Text3DGlyphSequenceStage();
    virtual ~Text3DGlyphSequenceStage();

    virtual void process() override;

public:
    gloperate::InputSlot<std::string> string;
    gloperate::InputSlot<gloperate_text::FontFace *> font;
    gloperate::InputSlot<gloperate::AbstractViewportCapability *> viewport;

    gloperate::Data<std::vector<gloperate_text::GlyphSequence>> sequences;

private:
    std::vector<std::string> m_modelStrings;
};
