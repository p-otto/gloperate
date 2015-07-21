
#include <gloperate/rendering/components/VirtualTimeComponent.h>

#include <gloperate/rendering/AbstractStage.h>


namespace gloperate
{
namespace glop2
{


VirtualTimeComponent::VirtualTimeComponent(AbstractStage & stage)
: AbstractComponent(stage)
{
    // Register component
    m_stage->addComponent(*this);

    // Register input slots
    m_stage->addInput        ("VirtualTime", VirtualTime);
    m_stage->addInput        ("TimeDelta",   TimeDelta);
    m_stage->addOptionalInput("Fps",         Fps);
}

VirtualTimeComponent::~VirtualTimeComponent()
{
}


} // namespace glop2
} // namespace gloperate
