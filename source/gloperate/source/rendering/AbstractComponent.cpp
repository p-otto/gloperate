
#include <gloperate/rendering/AbstractComponent.h>


namespace gloperate
{
namespace glop2
{


AbstractComponent::AbstractComponent(AbstractStage & stage)
: m_stage(&stage)
{
}

AbstractComponent::~AbstractComponent()
{
}

AbstractStage * AbstractComponent::stage() const
{
    return m_stage;
}


} // namespace glop2
} // namespace gloperate
