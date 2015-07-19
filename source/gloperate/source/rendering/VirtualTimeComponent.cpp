
#include <gloperate/rendering/VirtualTimeComponent.h>

#include <gloperate/rendering/AbstractStage.h>


namespace gloperate
{
namespace glop2
{


VirtualTimeComponent::VirtualTimeComponent(AbstractStage & stage)
: AbstractComponent(stage)
{
    // Register input slots
    m_stage->addInput("virtualTime", m_virtualTime);
}

VirtualTimeComponent::~VirtualTimeComponent()
{
}


} // namespace glop2
} // namespace gloperate
