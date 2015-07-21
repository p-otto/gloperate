
#include <gloperate/rendering/components/ViewportComponent.h>

#include <gloperate/rendering/AbstractStage.h>


namespace gloperate
{
namespace glop2
{


ViewportComponent::ViewportComponent(AbstractStage & stage)
: AbstractComponent(stage)
{
    // Register component
    m_stage->addComponent(*this);

    // Register input slots
    m_stage->addInput("Viewport",         Viewport);
    m_stage->addInput("ScreenSize",       ScreenSize);
    m_stage->addInput("DevicePixelRatio", DevicePixelRatio);
}

ViewportComponent::~ViewportComponent()
{
}


} // namespace glop2
} // namespace gloperate
