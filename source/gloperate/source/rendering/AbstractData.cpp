
#include <gloperate/rendering/AbstractData.h>

#include <algorithm>
#include <sstream>

//#include <gloperate/rendering/AbstractStage.h>


namespace gloperate
{
namespace glop2
{


AbstractData::AbstractData(const std::string & name)
: m_owner(nullptr)
, m_name(name)
{
}

AbstractData::~AbstractData()
{
}

bool AbstractData::hasName() const
{
    return !m_name.empty();
}

const std::string & AbstractData::name() const
{
    return m_name;
}

void AbstractData::setName(const std::string & name)
{
    m_name = name;
}

bool AbstractData::hasOwner() const
{
    return m_owner != nullptr;
}

const AbstractStage * AbstractData::owner() const
{
    return m_owner;
}

void AbstractData::setOwner(AbstractStage * owner)
{
    m_owner = owner;
}

void AbstractData::invalidate()
{
    invalidated();
}


} // namespace glop2
} // namespace gloperate
