
#pragma once


#include <memory>

#include <gloperate/ext-includes-begin.h>
#include <glm/glm.hpp>
#include <gloperate/ext-includes-end.h>

#include <globjects/base/ref_ptr.h>

#include <gloperate/painter/Painter.h>
#include <gloperate/rendering/Data.h>

#include <gloperate-qt/viewer/QtOpenGLWindowBase.h>
#include <gloperate-qt/viewer/TimePropagator.h>


namespace gloperate {
    class ResourceManager;
    namespace glop2 {
        class AbstractStage;
    }
}


namespace gloperate_qt
{


class TimerApi;


/**
*  @brief
*    Qt window that can be used for rendering with gloperate and OpenGL
*
*    This is the main rendering widget that displays a gloperate::AbstractStage
*    within a Qt application. For that to work, the stage has to provide at least
*    a ViewportComponent, to support screenshots, it also has to provide an
*    FramebufferComponent.
*
*    This class contains only the rendering widget itself, no other GUI elements.
*    For a fully-fledged application template, see gloperate_qt::Viewer.
*/
class GLOPERATE_QT_API QtOpenGLWindow : public QtOpenGLWindowBase
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] resourceManager
    *    Manager for loading/saving resources (i.e., textures, scenes)
    */
    QtOpenGLWindow(gloperate::ResourceManager & resourceManager);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] resourceManager
    *    Manager for loading/saving resources (i.e., textures, scenes)
    *  @param[in] format
    *    Surface format
    */
    QtOpenGLWindow(gloperate::ResourceManager & resourceManager, const QSurfaceFormat & format);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~QtOpenGLWindow();

    /**
    *  @brief
    *    Get used painter
    *
    *  @return
    *    Painter, can be nullptr
    */
    gloperate::Painter * painter() const;

    /**
    *  @brief
    *    Set used painter
    *
    *  @param[in] painter
    *    Painter, can be nullptr
    */
    void setPainter(gloperate::Painter * painter);

    /**
    *  @brief
    *    Get stage used for rendering into the widget
    *
    *  @return
    *    Rendering stage, can be nullptr
    */
    gloperate::glop2::AbstractStage * renderer() const;

    /**
    *  @brief
    *    Set stage used for rendering into the widget
    *
    *  @param[in] renderer
    *    Rendering stage, can be nullptr
    */
    void setRenderer(gloperate::glop2::AbstractStage * renderer);

    /**
    *  @brief
    *    Set scripting timer API
    *
    *  @param[in] timerAPI
    *    Scripting timer API, can be nullptr
    *
    *  @remarks
    *    This is necessary to propagate the
    *    nextTick-event to the timer API.
    */
    void setTimerApi(TimerApi * timerApi);


protected:
    virtual void onInitialize() override;
    virtual void onResize(QResizeEvent * event) override;
    virtual void onPaint() override;
    virtual void keyPressEvent(QKeyEvent * event) override;
    virtual void keyReleaseEvent(QKeyEvent * event) override;
    virtual void mouseMoveEvent(QMouseEvent * event) override;
    virtual void mousePressEvent(QMouseEvent * event) override;
    virtual void mouseReleaseEvent(QMouseEvent * event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent * event) override;
    virtual void wheelEvent(QWheelEvent * event) override;


protected:
    gloperate::ResourceManager      & m_resourceManager;  ///< Resource manager for loading assets
    gloperate::Painter              * m_painter;          ///< Currently used painter
    gloperate::glop2::AbstractStage * m_renderer;         ///< Rendering stage, can be nullptr
    std::unique_ptr<TimePropagator>   m_timePropagator;   ///< Time propagator for continous updates
    TimerApi                        * m_timerApi;         ///< Scripting timer API
    gloperate::glop2::Data<glm::vec4> m_viewport;         ///< Viewport coordinates (x, y, w, h) in real device coordinates
    gloperate::glop2::Data<glm::vec2> m_devicePixelRatio; ///< Ratio of device pixels to virtual pixels (keep in mind that m_viewport is already expressed in device pixels!)
};


} // namespace gloperate-qt
