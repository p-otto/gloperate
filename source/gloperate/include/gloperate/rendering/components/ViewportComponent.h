
#pragma once


#include <gloperate/ext-includes-begin.h>
#include <glm/glm.hpp>
#include <gloperate/ext-includes-end.h>

#include <gloperate/rendering/AbstractComponent.h>
#include <gloperate/rendering/InputSlot.h>


namespace gloperate
{
namespace glop2
{


/**
*  @brief
*    Component for stages that support rendering into different viewports
*/
class GLOPERATE_API ViewportComponent : public AbstractComponent
{
public:
    InputSlot<glm::vec4> Viewport;         ///< Viewport coordinates (x, y, w, h) in real device coordinates
    InputSlot<glm::vec2> ScreenSize;       ///< Screen size (w, h) in real device coordinates
    InputSlot<glm::vec2> DevicePixelRatio; ///< Ratio of device pixels to virtual pixels (keep in mind that m_viewport is already expressed in device pixels!)


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] stage
    *    Sage that owns the component
    */
    ViewportComponent(AbstractStage & stage);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ViewportComponent();


protected:
};


} // namespace glop2
} // namespace gloperate
