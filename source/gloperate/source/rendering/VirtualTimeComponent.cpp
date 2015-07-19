
#include <gloperate/rendering/VirtualTimeComponent.h>

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
    m_stage->addInput        ("virtualTime", m_virtualTime);
    m_stage->addInput        ("timeDelta",   m_timeDelta);
    m_stage->addOptionalInput("fps",         m_fps);
}

VirtualTimeComponent::~VirtualTimeComponent()
{
}


} // namespace glop2
} // namespace gloperate
