
#pragma once


#include <gloperate/plugin/StagePlugin.h>


namespace gloperate
{


template <typename StageType>
StagePlugin<StageType>::StagePlugin(
    const std::string & name
  , const std::string & description
  , const std::string & vendor
  , const std::string & version)
: AbstractStagePlugin(name, description, vendor, version)
{
}

template <typename StageType>
StagePlugin<StageType>::~StagePlugin()
{
}

template <typename StageType>
gloperate::glop2::AbstractStage * StagePlugin<StageType>::createStage(ResourceManager & resourceManager) const
{
    return new StageType(resourceManager, m_relDataPath);
}


} // namespace gloperate
