
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

    m_modelStrings = std::vector<std::string>{
                     std::string("Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall Left Wall "),
                     std::string("Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall Back Wall "),
                     std::string("Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall Right Wall "),
                     std::string("Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box Short Box "),
                     std::string("Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box Long Box "),
                     std::string("Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom Bottom "),
                     std::string("Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling Ceiling "),
                     std::string("Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp Lamp ")
                     };
}

Text3DGlyphSequenceStage::~Text3DGlyphSequenceStage()
{
}

void Text3DGlyphSequenceStage::process()
{
    const auto fontSize = 20.0f;
    const auto pixelPerInch = 72.0f;
    const auto margins = glm::vec4(0.f, 0.f, 0.f, 0.f);

    sequences.data().clear();
    sequences.data().resize(1+m_modelStrings.size());


    int i = 0;
    for(auto& curString : m_modelStrings)
    {
        sequences.data()[i].setString(stringzeug::encode(curString.data(), stringzeug::Encoding::UTF8));

        sequences.data()[i].setWordWrap(true);
        sequences.data()[i].setLineWidth(512.0f, fontSize, *font.data());
        sequences.data()[i].setAlignment(gloperate_text::Alignment::LeftAligned);
        sequences.data()[i].setLineAnchor(gloperate_text::LineAnchor::Ascent);
        sequences.data()[i].setTransform(glm::vec2(-1.0f, 1.0f), fontSize, *font.data()
            , { 512, 512 }, pixelPerInch, margins);
        i++;
    }

    sequences.data()[i].setString(stringzeug::encode(string.data(), stringzeug::Encoding::UTF8));

    sequences.data()[i].setWordWrap(true);
    sequences.data()[i].setLineWidth(512.0f, fontSize, *font.data());
    sequences.data()[i].setAlignment(gloperate_text::Alignment::LeftAligned);
    sequences.data()[i].setLineAnchor(gloperate_text::LineAnchor::Ascent);
    sequences.data()[i].setTransform(glm::vec2(-1.0f, 1.0f), fontSize, *font.data()
        , { 512, 512 }, pixelPerInch, margins);




    invalidateOutputs();
}
