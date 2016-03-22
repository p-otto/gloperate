
#pragma once


#include <gloperate/pipeline/PipelinePainter.h>

#include "Text3DPipeline.h"


class Text3DPainter : public gloperate::PipelinePainter
{
public:
    Text3DPainter(
        gloperate::ResourceManager & resourceManager
    ,   const cpplocate::ModuleInfo & moduleInfo);

protected:
    Text3DPipeline m_pipeline;
};
