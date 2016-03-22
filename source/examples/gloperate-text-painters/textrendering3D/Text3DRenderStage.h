
#pragma once

#include <string>
#include <vector>

#include <glm/fwd.hpp>

#include <gloperate/painter/AbstractTargetFramebufferCapability.h>
#include <gloperate/painter/AbstractViewportCapability.h>
#include <gloperate/painter/AbstractCameraCapability.h>
#include <gloperate/painter/AbstractPerspectiveProjectionCapability.h>

#include <gloperate/resources/ResourceManager.h>

#include <gloperate/pipeline/AbstractStage.h>
#include <gloperate/pipeline/Data.h>
#include <gloperate/pipeline/InputSlot.h>

#include <gloperate-text/GlyphVertexCloud.h>
#include <gloperate-text/GlyphRenderer.h>

namespace gloperate
{

    class AbstractViewportCapability;
    class PolygonalDrawable;

} // namespace gloperate


class Text3DRenderStage : public gloperate::AbstractStage
{
public:
    Text3DRenderStage();
    virtual ~Text3DRenderStage();

    virtual void initialize() override;
    virtual void process() override;

public:
    gloperate::InputSlot<std::vector<globjects::ref_ptr<globjects::Texture>>> textures;
    gloperate::InputSlot<gloperate::ResourceManager *> resourceManager;
    
    gloperate::InputSlot<gloperate::AbstractViewportCapability *> viewport;
    gloperate::InputSlot<gloperate::AbstractCameraCapability *> camera;
    gloperate::InputSlot<gloperate::AbstractPerspectiveProjectionCapability *> projection;

    gloperate::InputSlot<gloperate::AbstractTargetFramebufferCapability *> targetFramebuffer;

protected:
    std::unique_ptr<gloperate_text::GlyphRenderer> m_renderer;
    globjects::ref_ptr<globjects::Program> m_program;
    std::vector<gloperate::PolygonalDrawable> m_drawables;
};
