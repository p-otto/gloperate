
#include "Text3DPipeline.h"

#include <string>

#include <gloperate/gloperate.h>

#include <gloperate-text/Alignment.h>
#include <gloperate-text/LineAnchor.h>
#include <gloperate-text/stages/FontImporterStage.h>
#include <gloperate-text/stages/GlyphPreparationStage.h>
#include <gloperate-text/stages/GlyphRenderStage.h>

#include "Text3DGlyphSequenceStage.h"
#include "Text3DRenderStage.h"

namespace
{
    const auto lorem = 
R"(Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.)";
}

Text3DPipeline::Text3DPipeline()
: resourceManager(nullptr)
, fontFilename(gloperate::dataPath() + "/gloperate-text/fonts/opensansr36.fnt")
, string(lorem)
, targetFBO(nullptr)
, viewport(nullptr)
{
    auto fontImport = new gloperate_text::FontImporterStage;
    auto glyphSequence = new Text3DGlyphSequenceStage;
    auto glyphPreparation = new gloperate_text::GlyphPreparationStage;
    auto glyphRendering = new Text3DRenderStage;

    fontImport->resourceManager = resourceManager;
    fontImport->fontFilePath = fontFilename;

    glyphSequence->string = string;
    glyphSequence->font = fontImport->font;
    glyphSequence->viewport = viewport;

    glyphPreparation->font = fontImport->font;
    glyphPreparation->sequences = glyphSequence->sequences;
    glyphPreparation->optimized = gloperate::Data<bool>(false);
    
    glyphRendering->camera = camera;
    glyphRendering->projection = projection;
    glyphRendering->resourceManager = resourceManager;
    glyphRendering->vertexCloud = glyphPreparation->vertexCloud;
    glyphRendering->viewport = viewport;
    glyphRendering->targetFramebuffer = targetFBO;

    addStages(
        fontImport
    ,   glyphSequence
    ,   glyphPreparation
    ,   glyphRendering);
}

Text3DPipeline::~Text3DPipeline()
{
}
