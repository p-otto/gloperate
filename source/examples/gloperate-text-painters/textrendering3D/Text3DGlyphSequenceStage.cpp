
#include "Text3DGlyphSequenceStage.h"

#include <glm/vec2.hpp>

#include <stringzeug/conversion.h>

#include <gloperate/painter/AbstractViewportCapability.h>

#include <gloperate-text/Alignment.h>
#include <gloperate-text/LineAnchor.h>
#include <gloperate-text/GlyphSequence.h>

Text3DGlyphSequenceStage::Text3DGlyphSequenceStage()
    : AbstractStage("Text3DGlyphSequenceStage")
{
    addInput("string", string);
    addInput("font", font);
    addInput("viewport", viewport);

    addOutput("sequences", sequences);
}

Text3DGlyphSequenceStage::~Text3DGlyphSequenceStage()
{
}

void Text3DGlyphSequenceStage::process()
{
    sequences.data().clear();
    sequences.data().resize(1);

    const auto fontSize = 16.0f;
    const auto pixelPerInch = 72.0f;
    const auto margins = glm::vec4(0.f, 0.f, 0.f, 0.f);

    sequences.data()[0].setString(stringzeug::encode(string.data(), stringzeug::Encoding::UTF8));

    sequences.data()[0].setWordWrap(true);
    sequences.data()[0].setLineWidth(400.0f, fontSize, *font.data());
    sequences.data()[0].setAlignment(gloperate_text::Alignment::Centered);
    sequences.data()[0].setLineAnchor(gloperate_text::LineAnchor::Center);

    sequences.data()[0].setTransform(glm::vec2(0.0f, 0.5f), fontSize, *font.data()
        , { 512, 512 }, pixelPerInch, margins);

    invalidateOutputs();
}
