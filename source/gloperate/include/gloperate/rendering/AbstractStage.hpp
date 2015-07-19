
#pragma once


#include <gloperate/rendering/AbstractStage.h>


namespace gloperate
{
namespace glop2
{


template <typename ComponentType>
bool AbstractStage::supports() const
{
    return (this->component<ComponentType>() != nullptr);
}

template <typename ComponentType>
ComponentType * AbstractStage::component() const
{
    for (auto & comp : m_components)
    {
        ComponentType * typedComponent = dynamic_cast<ComponentType *>(comp);
        if (typedComponent != nullptr)
        {
            return typedComponent;
        }
    }

    return nullptr;
}


} // namespace glop2
} // namespace gloperate
