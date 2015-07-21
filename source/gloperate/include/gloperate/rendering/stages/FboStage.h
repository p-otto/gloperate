
#pragma once


#include <gloperate/rendering/AbstractStage.h>


namespace gloperate
{
namespace glop2
{


/**
*  @brief
*    Stage that creates and updates an FBO
*/
class GLOPERATE_API FboStage : public AbstractStage
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Object name (can be chosen freely, but must not include whitespace)
    *  @param[in] resourceManager
    *    Resource manager, e.g., to load and save assets
    *  @param[in] relDataPath
    *    Path to data directory (usually "", unless loaded from plugins)
    */
    FboStage(const std::string & name, ResourceManager & resourceManager, const std::string & relDataPath);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~FboStage();


protected:
    virtual void initialize() override;
    virtual void process() override;
};


} // namespace glop2
} // namespace gloperate
