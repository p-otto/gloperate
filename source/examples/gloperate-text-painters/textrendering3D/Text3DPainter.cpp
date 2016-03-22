
#include "Text3DPainter.h"

#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>

#include <reflectionzeug/property/extensions/GlmProperties.h>

#include <gloperate/painter/ViewportCapability.h>
#include <gloperate/painter/CameraCapability.h>
#include <gloperate/painter/PerspectiveProjectionCapability.h>
#include <gloperate/painter/TargetFramebufferCapability.h>
#include <gloperate/painter/TypedRenderTargetCapability.h>

#include <gloperate-text/Alignment.h>
#include <gloperate-text/LineAnchor.h>

#include <QtWidgets/qapplication.h>
#include <QtGui/qscreen.h>


Text3DPainter::Text3DPainter(gloperate::ResourceManager & resourceManager, const cpplocate::ModuleInfo & moduleInfo)
    : PipelinePainter("TextRendering", resourceManager, moduleInfo, m_pipeline)
{
    auto targetFBO = addCapability(new gloperate::TargetFramebufferCapability());
    auto viewport = addCapability(new gloperate::ViewportCapability());
    auto camera = addCapability(new gloperate::CameraCapability());
    auto projection = addCapability(new gloperate::PerspectiveProjectionCapability(viewport));

    m_pipeline.targetFBO.setData(targetFBO);
    m_pipeline.viewport.setData(viewport);
    m_pipeline.camera.setData(camera);
    m_pipeline.projection.setData(projection);
    m_pipeline.resourceManager.setData(&resourceManager);

    targetFBO->changed.connect([this]() { m_pipeline.targetFBO.invalidate(); });
    viewport->changed.connect([this]() { m_pipeline.viewport.invalidate(); });
    camera->changed.connect([this]() { m_pipeline.camera.invalidate(); });
    projection->changed.connect([this]() { m_pipeline.projection.invalidate(); });

    addProperty(createProperty("GlyphSequence", m_pipeline.string));

    addProperty(createProperty("Filename", m_pipeline.fontFilename));

    auto screen = QApplication::primaryScreen();
    assert(screen);
}
