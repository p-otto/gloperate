
#include <gloperate-version.h>
#include <gloperate/plugin/plugin_api.h>

#include "logo/Logo.h"


GLOPERATE_PLUGIN_LIBRARY

    GLOPERATE_STAGE_PLUGIN(Logo
    , "Logo"
    , "Renders a rotating quad, featuring textures, animation, and cameras"
    , GLOPERATE_AUTHOR_ORGANIZATION
    , "v1.0.0" )

GLOPERATE_PLUGIN_LIBRARY_END
