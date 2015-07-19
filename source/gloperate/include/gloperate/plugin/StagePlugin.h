
#pragma once


#include <gloperate/plugin/Plugin.h>


namespace gloperate
{


class ResourceManager;

namespace glop2
{
    class AbstractStage;
}


/**
*  @brief
*    Represents a plugin that contains an AbstractStage implementation
*/
class GLOPERATE_API AbstractStagePlugin : public Plugin
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Plugin name
    *  @param[in] description
    *    Plugin description
    *  @param[in] vendor
    *    Vendor name
    *  @param[in] version
    *    Plugin version
    */
    AbstractStagePlugin(
        const std::string & name
    ,   const std::string & description
    ,   const std::string & vendor
    ,   const std::string & version);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractStagePlugin();

    /**
    *  @brief
    *    Create stage
    *
    *  @param[in] resourceManager
    *    Resource manager for the stage to load external data
    *
    *  @return
    *    Pointer to newly created stage, nullptr on error
    */
    virtual gloperate::glop2::AbstractStage * createStage(ResourceManager & resourceManager) const = 0;
};


/**
*  @brief
*    Concrete implementation of a stage plugin
*/
template <typename StageType>
class StagePlugin : public AbstractStagePlugin
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Plugin name
    *  @param[in] description
    *    Plugin description
    *  @param[in] vendor
    *    Vendor name
    *  @param[in] version
    *    Plugin version
    */
    StagePlugin(
        const std::string & name
    ,   const std::string & description
    ,   const std::string & vendor
    ,   const std::string & version);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StagePlugin();

    // Virtual AbstractStagePlugin interface
    virtual gloperate::glop2::AbstractStage * createStage(ResourceManager & resourceManager) const override;
};


} // namespace gloperate


#include <gloperate/plugin/StagePlugin.hpp>
