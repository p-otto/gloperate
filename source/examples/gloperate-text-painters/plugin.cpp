
#include <gloperate/gloperate-version.h>
#include <gloperate/plugin/plugin_api.h>

#include "textrenderingpipeline/TextRenderingPainter.h"
#include "textrendering3D/Text3DPainter.h"


GLOPERATE_PLUGIN_LIBRARY
    
    GLOPERATE_PAINTER_PLUGIN(TextRenderingPainter
    , "TextRenderingPipeline"
    , "Text rendering demo"
    , GLOPERATE_AUTHOR_ORGANIZATION
    , "v1.0.0" )

    GLOPERATE_PAINTER_PLUGIN(Text3DPainter
    , "Text3DPainter"
    , "Text rendering demo"
    , GLOPERATE_AUTHOR_ORGANIZATION
    , "v1.0.0")

GLOPERATE_PLUGIN_LIBRARY_END
