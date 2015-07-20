
#pragma once


#include <gloperate/base/collection.hpp>

#include <gloperate/rendering/Pipeline.h>
#include <gloperate/rendering/AbstractData.h>
#include <gloperate/rendering/Data.h>


namespace gloperate
{
namespace glop2
{


template <typename T>
Data<T> * Pipeline::getOutput(const std::string & name) const
{
    for (AbstractData * output : findOutputs(name))
    {
        Data<T> * data = dynamic_cast<Data<T> *>(output);
        if (data)
        {
            return data;
        }
    }

    return nullptr;
}

template <typename T>
Data<T> * Pipeline::getOutput() const
{
    return dynamic_cast<Data<T> *>(collection::detect(allOutputs(), [] (AbstractData * data)
    {
        return dynamic_cast<Data<T> *>(data) != nullptr;
    }, nullptr));
}

template <typename T>
Data<T> * Pipeline::getParameter(const std::string & name) const
{
    return dynamic_cast<Data<T> *>(findParameter(name));
}

template <typename T>
Data<T> * Pipeline::getParameter() const
{
    return dynamic_cast<Data<T> *>(collection::detect(m_parameters, [] (AbstractData * parameter)
    {
        return dynamic_cast<Data<T> *>(parameter) != nullptr;
    }, nullptr));
}

template <typename T>
Data<T> * Pipeline::addConstantParameter(const T & value)
{
    auto constant = new Data<T>(value);

    m_constantParameters.push_back(constant);

    return constant;
}

template<typename... Args>
void Pipeline::addStages(AbstractStage * stage, Args... pipeline)
{
    addStage(stage);
    addStages(std::forward<Args>(pipeline)...);
}


} // namespace glop2
} // namespace gloperate
