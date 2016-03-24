
#pragma once

#include <string>
#include <vector>

#include <glm/fwd.hpp>

#include <gloperate/painter/AbstractTargetFramebufferCapability.h>
#include <gloperate/painter/AbstractViewportCapability.h>
#include <gloperate/painter/AbstractCameraCapability.h>
#include <gloperate/painter/AbstractPerspectiveProjectionCapability.h>


#include <gloperate/pipeline/AbstractStage.h>
#include <gloperate/pipeline/Data.h>
#include <gloperate/pipeline/InputSlot.h>

#include <gloperate-text/GlyphVertexCloud.h>
#include <gloperate-text/GlyphRenderer.h>

namespace globjects
{
    class Texture;
}

namespace gloperate
{

    class AbstractViewportCapability;
    class PolygonalDrawable;
    class ScreenAlignedQuad;

} // namespace gloperate


class Text3dPostprocessingStage : public gloperate::AbstractStage
{
public:
    Text3dPostprocessingStage();
    virtual ~Text3dPostprocessingStage();

    virtual void initialize() override;
    virtual void process() override;

public:
    gloperate::InputSlot<globjects::ref_ptr<globjects::Texture>> color;
    gloperate::InputSlot<globjects::ref_ptr<globjects::Texture>> normal;
    gloperate::InputSlot<globjects::ref_ptr<globjects::Texture>> depth;
    
    gloperate::InputSlot<gloperate::AbstractViewportCapability *> viewport;
    gloperate::InputSlot<gloperate::AbstractCameraCapability *> camera;
    gloperate::InputSlot<gloperate::AbstractPerspectiveProjectionCapability *> projection;

protected:
    void blurSSAO();
    void resizeTextures();

    globjects::ref_ptr<gloperate::ScreenAlignedQuad> m_ssaoQuad;
    globjects::ref_ptr<gloperate::ScreenAlignedQuad> m_blurQuad;
    globjects::ref_ptr<gloperate::ScreenAlignedQuad> m_mixQuad;

    globjects::ref_ptr<globjects::Framebuffer> m_fbo;
    globjects::ref_ptr<globjects::Framebuffer> m_blitFbo;
    globjects::ref_ptr<globjects::Texture> m_noise; 
    globjects::ref_ptr<globjects::Texture> m_kernel;

    globjects::ref_ptr<globjects::Texture> m_SSAOTexture;
    globjects::ref_ptr<globjects::Texture> m_tempBlurredTexture;
    globjects::ref_ptr<globjects::Texture> m_blurredTexture;
};
