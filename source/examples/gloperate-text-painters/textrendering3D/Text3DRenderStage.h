
#pragma once

#include <vector>

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
    gloperate::InputSlot<bool> opaque;

    gloperate::Data<globjects::ref_ptr<globjects::Texture>> color;
    gloperate::Data<globjects::ref_ptr<globjects::Texture>> normal;
    gloperate::Data<globjects::ref_ptr<globjects::Texture>> depth;

protected:
    void resizeTexture();

    globjects::ref_ptr<globjects::Framebuffer> m_fbo;
    std::unique_ptr<gloperate_text::GlyphRenderer> m_renderer;
    globjects::ref_ptr<globjects::Program> m_program;
    std::vector<gloperate::PolygonalDrawable> m_drawables;
};
