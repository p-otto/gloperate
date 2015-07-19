
#include <gloperate/rendering/AbstractInputSlot.h>

#include <sstream>
#include <algorithm>

//#include <gloperate/rendering/AbstractStage.h>


namespace gloperate
{
namespace glop2
{


AbstractInputSlot::AbstractInputSlot(const std::string & name)
: m_owner(nullptr)
, m_name(name)
, m_hasChanged(true)
, m_isOptional(false)
, m_isFeedback(false)
{
}

AbstractInputSlot::~AbstractInputSlot()
{
}

bool AbstractInputSlot::hasName() const
{
    return !m_name.empty();
}

const std::string & AbstractInputSlot::name() const
{
    return m_name;
}

void AbstractInputSlot::setName(const std::string & name)
{
    m_name = name;
}

bool AbstractInputSlot::hasOwner() const
{
    return m_owner != nullptr;
}

const AbstractStage * AbstractInputSlot::owner() const
{
    return m_owner;
}

bool AbstractInputSlot::hasChanged() const
{
    return m_hasChanged;
}

void AbstractInputSlot::changed()
{
    m_hasChanged = true;
}

void AbstractInputSlot::processed()
{
    m_hasChanged = false;
}

bool AbstractInputSlot::isOptional() const
{
    return m_isOptional;
}

void AbstractInputSlot::setOptional(bool optional)
{
    m_isOptional = optional;
}

bool AbstractInputSlot::isFeedback() const
{
    return m_isFeedback;
}

void AbstractInputSlot::setFeedback(bool isFeedback)
{
    m_isFeedback = isFeedback;

    connectionChanged();
}

bool AbstractInputSlot::isConnected() const
{
    return connectedData() != nullptr;
}

bool AbstractInputSlot::isUsable() const
{
    return isOptional() || isConnected();
}

void AbstractInputSlot::setOwner(AbstractStage * owner)
{
    m_owner = owner;
}


} // namespace glop2
} // namespace gloperate
