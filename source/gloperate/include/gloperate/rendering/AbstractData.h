
#pragma once


#include <string>

#include <signalzeug/Signal.h>

#include <gloperate/gloperate_api.h>


namespace gloperate
{
namespace glop2
{


class AbstractStage;


/**
*  @brief
*    Base class for typed data containers
*
*  @see
*    Data
*/
class GLOPERATE_API AbstractData
{
    friend class AbstractStage;


public:
    signalzeug::Signal<> invalidated;


public:
    AbstractData(const std::string & name = "");
    virtual ~AbstractData();

    virtual std::string type() const = 0;

    bool hasName() const;
    std::string name() const;
    void setName(const std::string & name);
    std::string qualifiedName() const;

    bool hasOwner() const;
    const AbstractStage * owner() const;

    void invalidate();


protected:
    void setOwner(AbstractStage * owner);


protected:
    AbstractStage * m_owner;    ///< Stage that owns the data, can be nullptr
    std::string     m_name;     ///< Name of data container
};


} // namespace glop2
} // namespace gloperate
