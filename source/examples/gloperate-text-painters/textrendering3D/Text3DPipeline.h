
#pragma once

#include <string>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <reflectionzeug/base/FilePath.h>
//#include <reflectionzeug/base/Color.h>

#include <gloperate/painter/AbstractViewportCapability.h>
#include <gloperate/painter/AbstractTargetFramebufferCapability.h>
#include <gloperate/painter/AbstractCameraCapability.h>
#include <gloperate/painter/AbstractPerspectiveProjectionCapability.h>
#include <gloperate/pipeline/AbstractPipeline.h>
#include <gloperate/pipeline/Data.h>
#include <gloperate/resources/ResourceManager.h>

namespace gloperate
{
    class AbstractVirtualTimeCapability;
}

namespace gloperate_text
{
    enum class Alignment : unsigned char;
    enum class LineAnchor : unsigned char;
}


class Text3DPipeline : public gloperate::AbstractPipeline
{
public:
    Text3DPipeline();
    virtual ~Text3DPipeline();

public:
    gloperate::Data<gloperate::ResourceManager *> resourceManager;
    gloperate::Data<reflectionzeug::FilePath> fontFilename;

    gloperate::Data<std::string> string;

    gloperate::Data<gloperate::AbstractVirtualTimeCapability *> time;

    gloperate::Data<gloperate::AbstractTargetFramebufferCapability *> targetFBO;
    gloperate::Data<gloperate::AbstractViewportCapability *> viewport;
    gloperate::Data<gloperate::AbstractCameraCapability *> camera;
    gloperate::Data<gloperate::AbstractPerspectiveProjectionCapability *> projection;
};
