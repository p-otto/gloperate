
#include "Text3DPipeline.h"

#include <string>

#include <gloperate/gloperate.h>

#include <gloperate-text/Alignment.h>
#include <gloperate-text/LineAnchor.h>
#include <gloperate-text/stages/FontImporterStage.h>
#include <gloperate-text/stages/GlyphRenderStage.h>

#include "Text3DGlyphSequenceStage.h"
#include "Text3DRenderStage.h"
#include "Text3DTexturePreparationStage.h"
#include "Text3DPostprocessingStage.h"

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
    auto texturePreparation = new Text3DTexturePreparationStage;
    auto sceneRendering = new Text3DRenderStage;
    auto postprocessing = new Text3dPostprocessingStage;

    fontImport->resourceManager = resourceManager;
    fontImport->fontFilePath = fontFilename;

    glyphSequence->string = string;
    glyphSequence->font = fontImport->font;
    glyphSequence->viewport = viewport;

    texturePreparation->font = fontImport->font;
    texturePreparation->sequences = glyphSequence->sequences;
    
    sceneRendering->camera = camera;
    sceneRendering->projection = projection;
    sceneRendering->resourceManager = resourceManager;
    sceneRendering->textures = texturePreparation->textures;
    sceneRendering->viewport = viewport;

    postprocessing->color = sceneRendering->color;
    postprocessing->normal = sceneRendering->normal;
    postprocessing->depth = sceneRendering->depth;
    postprocessing->camera = camera;
    postprocessing->projection = projection;
    postprocessing->viewport = viewport;

    addStages(
        fontImport
    ,   glyphSequence
    ,   texturePreparation
    ,   sceneRendering
    ,   postprocessing);
}

Text3DPipeline::~Text3DPipeline()
{
}
