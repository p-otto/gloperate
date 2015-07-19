
#pragma once


#include <gloperate/rendering/AbstractComponent.h>
#include <gloperate/rendering/InputSlot.h>


namespace gloperate
{
namespace glop2
{


/**
*  @brief
*    Component for stages that support a virtual time input
*/
class GLOPERATE_API VirtualTimeComponent : public AbstractComponent
{
public:
    InputSlot<float> m_virtualTime;     ///< Virtual time (in seconds)


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] stage
    *    Sage that owns the component
    */
    VirtualTimeComponent(AbstractStage & stage);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~VirtualTimeComponent();


protected:
};


} // namespace glop2
} // namespace gloperate
