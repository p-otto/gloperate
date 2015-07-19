
#include <gloperate/rendering/InputSlot.h>

#include <iostream>


namespace gloperate
{
namespace glop2
{


void printIncompatibleMessage(
    const AbstractInputSlot * slot, 
    const std::string & typeName,                          
    const AbstractData & data) 
{
    std::cout
        << "Trying to connect incompatible type "
        << data.name() << " (" << data.type() << ")"
        << " to "
        << slot->name() << " (" << typeName << ")"
        << std::endl;
}


} // namespace glop2
} // namespace gloperate
