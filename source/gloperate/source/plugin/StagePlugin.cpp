
#include <gloperate/plugin/StagePlugin.h>


namespace gloperate
{


AbstractStagePlugin::AbstractStagePlugin(
    const std::string & name
  , const std::string & description
  , const std::string & vendor
  , const std::string & version)
: Plugin("Stage", name, description, vendor, version)
{
}

AbstractStagePlugin::~AbstractStagePlugin()
{
}


} // namespace gloperate
