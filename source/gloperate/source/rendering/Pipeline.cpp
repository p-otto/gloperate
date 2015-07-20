
#include <gloperate/rendering/Pipeline.h>

#include <cassert>
#include <string>
#include <algorithm>
#include <set>
#include <iostream>

#include <gloperate/base/collection.hpp>

#include <gloperate/rendering/AbstractStage.h>
#include <gloperate/rendering/AbstractInputSlot.h>
#include <gloperate/rendering/Data.h>


using namespace collection;


namespace gloperate
{
namespace glop2
{


Pipeline::Pipeline(const std::string & name)
:   m_initialized(false)
,   m_name(name)
,   m_dependenciesSorted(false)
{
}

Pipeline::~Pipeline()
{
    for (auto & stage : m_stages)
    {
        delete stage;
    }

    for (auto & constantParameter : m_constantParameters)
    {
        delete constantParameter;
    }
}

const std::string & Pipeline::name() const
{
    return m_name;
}

void Pipeline::setName(const std::string & name)
{
    m_name = name;
}

bool Pipeline::hasName() const
{
    return !m_name.empty();
}

std::string Pipeline::asPrintable() const
{
    if (!hasName())
        return "<unnamed>";

    std::string n = name();
    std::replace(n.begin(), n.end(), ' ', '_');

    return n;
}

void Pipeline::addStage(AbstractStage * stage)
{
    stage->dependenciesChanged.connect([this]() { m_dependenciesSorted = false; });
    m_stages.push_back(stage);
}

void Pipeline::addParameter(AbstractData * parameter)
{
    m_parameters.push_back(parameter);
}

void Pipeline::shareData(const AbstractData* data)
{
    assert(data != nullptr);

    m_sharedData.push_back(data);
}

void Pipeline::shareDataFrom(const AbstractInputSlot& slot)
{
    shareData(slot.connectedData());
}

void Pipeline::addParameter(const std::string & name, AbstractData * parameter)
{
    parameter->setName(name);
    addParameter(parameter);
}

const std::vector<AbstractStage *> & Pipeline::stages() const
{
    return m_stages;
}

const std::vector<AbstractData *> & Pipeline::parameters() const
{
    return m_parameters;
}

std::vector<AbstractInputSlot *> Pipeline::allInputs() const
{
    return flatten(collect(stages(), [](const AbstractStage * stage) { return stage->allInputs(); }));
}

std::vector<AbstractData *> Pipeline::allOutputs() const
{
    return flatten(collect(stages(), [](const AbstractStage * stage) { return stage->allOutputs(); }));
}

AbstractData * Pipeline::findParameter(const std::string & name) const
{
    return detect(m_parameters, [&name](AbstractData * parameter) { return (parameter->name() == name); }, nullptr);
}

std::vector<AbstractData *> Pipeline::findOutputs(const std::string & name) const
{
    return select(allOutputs(), [&name](AbstractData * data) { return (data->name() == name); });
}

void Pipeline::execute()
{
    if (!m_initialized)
    {
        return;
    }

    for (auto & stage: m_stages)
    {
        stage->execute();
    }
}

bool Pipeline::isInitialized() const
{
    return m_initialized;
}

void Pipeline::initialize()
{
    if (m_initialized)
        return;

    m_initialized = initializeStages();
}

bool Pipeline::initializeStages()
{
    if (!m_dependenciesSorted)
    {
        if (!sortDependencies())
            return false;
    }

    for (auto & stage : m_stages)
    {
        stage->init();
    }

    return true;
}

bool Pipeline::sortDependencies()
{
    if (m_dependenciesSorted)
        return true;

    m_dependenciesSorted = tsort(m_stages);
    return m_dependenciesSorted;
}

void Pipeline::addStages()
{
}

bool Pipeline::tsort(std::vector<AbstractStage *> & stages)
{
    auto couldBeSorted = true;
    std::vector<AbstractStage *> sorted;
    std::set<AbstractStage *> touched;

    std::function<void(AbstractStage *)> visit = [&](AbstractStage * stage)
    {
        if (!couldBeSorted)
        {
            sorted.push_back(stage);
            return;
        }

        if (touched.count(stage) > 0)
        {
            std::cerr << "Pipeline is not a directed acyclic graph" << std::endl;
            couldBeSorted = false;
            sorted.push_back(stage);
            return;
        }

        touched.insert(stage);

        for (auto stageIt = stages.begin(); stageIt != stages.end(); /* nop */)
        {
            if (!stage->requires(*stageIt, false))
            {
                ++stageIt;
                continue;
            }

            auto nextStage = *stageIt;
            stages.erase(stageIt);
            visit(nextStage);

            stageIt = stages.begin();
        }

        sorted.push_back(stage);
    };

    while (!stages.empty())
    {
        auto stageIt = stages.begin();
        auto stage = *stageIt;
        stages.erase(stageIt);
        visit(stage);
    }

    stages = sorted;

    return couldBeSorted;
}


} // namespace glop2
} // namespace gloperate
