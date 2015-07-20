
#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

#include <gloperate/rendering/AbstractStage.h>


namespace gloperate
{
namespace glop2
{


class AbstractData;
class AbstractInputSlot;

template <typename T>
class Data;


/**
*  @brief
*    Rendering pipeline
*
*    A pipeline describes a rendering or computation process.
*    It contains a number of stages, which are executed in a
*    defined order and only when needed.
*
*    Rendering stages provide data containers and input
*    slots, which can be connected to each other. Using
*    these data objects, a stage announces which input and
*    output data it needs or provides. Using this, it can be
*    determined which stage has to be executed and in what order
*    the stages are processed.
*
*  @see AbstractStage
*  @see Data
*  @see InputSlot
*/
class GLOPERATE_API Pipeline : public AbstractStage
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Object name (can be chosen freely, but must not include whitespace)
    *  @param[in] resourceManager
    *    Resource manager, e.g., to load and save assets
    *  @param[in] relDataPath
    *    Path to data directory (usually "", unless loaded from plugins)
    */
    Pipeline(const std::string & name, ResourceManager & resourceManager, const std::string & relDataPath);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Pipeline();

    // Fixes issues with MSVC2013 Update 3
    Pipeline(const Pipeline & rhs) = delete;
    Pipeline(Pipeline && rhs) = delete;
    Pipeline & operator=(const Pipeline & rhs) = delete;
    Pipeline & operator=(Pipeline && rhs) = delete;

    std::vector<AbstractInputSlot *> allInputs() const;

    std::vector<AbstractData *> allOutputs() const;
    template <typename T> Data<T> * getOutput(const std::string & name) const;
    template <typename T> Data<T> * getOutput() const;
    std::vector<AbstractData *> findOutputs(const std::string & name) const;

    const std::vector<AbstractData *> & parameters() const;
    template <typename T> Data<T> * getParameter(const std::string & name) const;
    template <typename T> Data<T> * getParameter() const;
    void addParameter(AbstractData * parameter);
    void addParameter(const std::string & name, AbstractData * parameter);
    template <typename T> Data<T> * addConstantParameter(const T & value);
    AbstractData * findParameter(const std::string & name) const;

    void shareData(const AbstractData * data);
    void shareDataFrom(const AbstractInputSlot & slot);

    const std::vector<AbstractStage *> & stages() const;
    virtual void addStage(AbstractStage * stage);
    template<typename... Args> void addStages(AbstractStage * stage, Args... pipeline);

    bool isInitialized() const;
    void initialize();

    virtual void execute();


protected: 
    bool sortDependencies();
    bool initializeStages();

    static bool tsort(std::vector<AbstractStage *> & stages);


protected:
    std::vector<AbstractStage *>      m_stages;
    std::vector<AbstractData *>       m_constantParameters;
    std::vector<AbstractData *>       m_parameters;
    std::vector<const AbstractData *> m_sharedData;
    bool                              m_initialized;
    bool                              m_dependenciesSorted;
};


} // namespace glop2
} // namespace gloperate


#include <gloperate/rendering/Pipeline.hpp>
