
#pragma once


#include <set>
#include <string>

#include <signalzeug/Signal.h>

#include <globjects/base/CachedValue.h>

#include <gloperate/gloperate_api.h>


namespace gloperate
{
namespace glop2
{


class AbstractInputSlot;
class AbstractData;


/**
*  @brief
*    Rendering stage
*
*    A rendering stage executes a specific task in a rendering
*    or processing technique. It can, e.g., be called by a viewer
*    to render into the viewer's framebuffer, or it can be part
*    of a pipeline.
*
*    A stage can define input slots, which represent the data
*    needed by the stage to operate, and output data, which can
*    represent additional data produced by the stage. These input
*    and output slots also determine the dependencies and order
*    of execution of stages in a pipeline. In addition to that,
*    addDependency() can be used to add manual dependencies between
*    stages that are not defined by data connections.
*
*    A stage is only executed when needed, i.e., when any of its
*    inputs data has been modified, when it has no input slots, or
*    if setAlwaysProcess() is set to true. Within the stage's
*    implementation, scheduleProcess() can be called to trigger a
*    processing of the stage in the next message loop cycle.
*
*  @see AbstractPipeline
*  @see Data
*  @see InputSlot
*/
class GLOPERATE_API AbstractStage
{
public:
    signalzeug::Signal<> dependenciesChanged;


public:
    AbstractStage(const std::string & name = "");
    virtual ~AbstractStage();

    bool hasName() const;
    const std::string & name() const;
    void setName(const std::string & name);

    bool isEnabled() const;
    void setEnabled(bool enabled);

    bool isAlwaysProcess() const;
    void setAlwaysProcess(bool alwaysProcess);

    const std::set<AbstractInputSlot*> & inputs() const;
    std::set<AbstractInputSlot*> allInputs() const;
    void addInput(const std::string & name, AbstractInputSlot & input);
    void shareInput(AbstractInputSlot * input);
    void addFeedbackInput(const std::string & name, AbstractInputSlot & input);
    void addOptionalInput(const std::string & name, AbstractInputSlot & input);

    const std::set<AbstractData*> & outputs() const;
    std::set<AbstractData*> allOutputs() const;
    void addOutput(const std::string & name, AbstractData & output);
    void shareOutput(AbstractData * output);

    void invalidateOutputs();

    void addDependency(AbstractStage * stage);

    bool requires(const AbstractStage * stage, bool recursive = true) const;

    void scheduleProcess();

    bool execute();


protected:
    bool needsToProcess() const;
    bool inputsUsable() const;
    void markInputsProcessed();

    virtual void initialize() = 0;
    virtual void process() = 0;


protected:
    bool m_enabled;
    bool m_alwaysProcess;
    bool m_processScheduled;
    std::string m_name;

    globjects::CachedValue<bool> m_usable;

    std::set<AbstractData*>      m_outputs;
    std::set<AbstractData*>      m_sharedOutputs;
    std::set<AbstractInputSlot*> m_inputs;
    std::set<AbstractInputSlot*> m_sharedInputs;
    std::set<AbstractStage*>     m_dependencies;    ///< Additional manual dependencies not expressed by data connections


private:
    AbstractStage(const AbstractStage &) = delete;
};


} // namespace glop2
} // namespace gloperate
