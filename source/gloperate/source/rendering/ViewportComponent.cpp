
#include <gloperate/rendering/ViewportComponent.h>

#include <gloperate/rendering/AbstractStage.h>


namespace gloperate
{
namespace glop2
{


ViewportComponent::ViewportComponent(AbstractStage & stage)
: AbstractComponent(stage)
{
    // Register input slots
    m_stage->addInput("viewport",         m_viewport);
    m_stage->addInput("devicePixelRatio", m_devicePixelRatio);
}

ViewportComponent::~ViewportComponent()
{
}


} // namespace glop2
} // namespace gloperate
