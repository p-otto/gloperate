
#pragma once


#include <gloperate/gloperate_api.h>


namespace gloperate
{
namespace glop2
{


class AbstractStage;


/**
*  @brief
*    Base class for stage components
*
*    Stage components represent reusable parts of rendering stages, usually containing
*    input slots and output data for a specific use case. They are used to communicate
*    capabilities of a rendering stage to the outside world, e.g., by providing a
*    ViewportComponent, a rendering stage signals that it is capable of rendering into
*    arbitrary viewports, which is required for a stage to be used as a rendering stage
*    of a viewer. Other components may be required for certain tools, such as taking
*    screenshots from a render stage.
*/
class GLOPERATE_API AbstractComponent
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] stage
    *    Sage that owns the component
    */
    AbstractComponent(AbstractStage & stage);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractComponent();

    /**
    *  @brief
    *    Get stage
    *
    *  @return
    *    Stage that owns the component (never nullptr)
    */
    AbstractStage * stage() const;


protected:
    AbstractStage * m_stage;    ///< Stage that owns the component (never nullptr)
};


} // namespace glop2
} // namespace gloperate
