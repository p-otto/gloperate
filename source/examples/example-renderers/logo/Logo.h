
#pragma once


#include <reflectionzeug/base/FilePath.h>
#include <reflectionzeug/base/Color.h>

#include <globjects/base/ref_ptr.h>
#include <globjects/VertexArray.h>
#include <globjects/Buffer.h>
#include <globjects/Program.h>
#include <globjects/Shader.h>
#include <globjects/Texture.h>

#include <gloperate/rendering/AbstractStage.h>
#include <gloperate/rendering/ViewportComponent.h>
#include <gloperate/rendering/VirtualTimeComponent.h>
#include <gloperate/painter/Camera.h>


namespace gloperate 
{
    class ResourceManager;
}


class Logo : public gloperate::glop2::AbstractStage
{
public:
    // Stage components
    gloperate::glop2::ViewportComponent    m_viewportComponent;
    gloperate::glop2::VirtualTimeComponent m_virtualTimeComponent;


public:
    Logo(gloperate::ResourceManager & resourceManager, const std::string & relDataPath);
    virtual ~Logo();

    bool animation() const;
    void setAnimation(const bool & enabled);

    reflectionzeug::Color background() const;
    void setBackground(const reflectionzeug::Color & color);

    reflectionzeug::FilePath texture() const;
    void setTexture(const reflectionzeug::FilePath & filename);


protected:
    virtual void initialize();
    virtual void process();


protected:
    void createAndSetupCamera();
    void createAndSetupTexture();
    void createAndSetupGeometry();


protected:
    // Parameters
    bool                     m_animation;
    reflectionzeug::Color    m_background;
    reflectionzeug::FilePath m_textureFilename;

    // Data
    globjects::ref_ptr<gloperate::Camera>       m_camera;
    globjects::ref_ptr<globjects::VertexArray>  m_vao;
    globjects::ref_ptr<globjects::Buffer>       m_buffer;
    globjects::ref_ptr<globjects::Program>      m_program;
    globjects::ref_ptr<globjects::Shader>       m_vertexShader;
    globjects::ref_ptr<globjects::Shader>       m_fragmentShader;
    globjects::ref_ptr<globjects::Texture>      m_texture;
    float                                       m_angle;
};
