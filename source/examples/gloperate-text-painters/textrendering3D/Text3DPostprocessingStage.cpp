
#include "Text3DPostprocessingStage.h"

#include <glm/gtc/random.hpp>

#include <glbinding/gl/gl.h>

#include <globjects/Framebuffer.h>
#include <globjects/Texture.h>

#include <gloperate/base/make_unique.hpp>
#include <gloperate/gloperate.h>
#include <gloperate/primitives/ScreenAlignedQuad.h>

using gloperate::make_unique;

using namespace gl;
using gl::GLenum;

namespace
{
    std::vector<glm::vec3> ssaoKernel(unsigned int size)
    {
        static const auto minDistance = 0.1f;
        const auto inverseSize = 1.f / static_cast<float>(size);

        auto kernel = std::vector<glm::vec3>();

        if (size == 1)
        {
            kernel.push_back(glm::vec3(0.f));

            return kernel;
        }

        while (kernel.size() < size)
        {
            auto v = glm::sphericalRand(1.f);
            v.z = glm::abs(v.z);
            if (v.z < 0.1)
                continue;

            auto scale = static_cast<float>(kernel.size()) * inverseSize;
            scale = scale * scale * (1.f - minDistance) + minDistance;

            v *= scale;

            kernel.push_back(v);
        }

        return kernel;
    }

    std::vector<glm::vec3> ssaoNoise(const unsigned int size)
    {
        auto kernel = std::vector<glm::vec3>();

        for (auto y = 0u; y < size; ++y)
        {
            for (auto x = 0u; x < size; ++x)
            {
                kernel.push_back(glm::vec3(glm::circularRand(1.f), 0.0f));
            }
        }

        return kernel;
    }

    globjects::Texture* ssaoKernelTexture(unsigned int size)
    {
        auto texture = new globjects::Texture(gl::GL_TEXTURE_1D);
        texture->setParameter(gl::GL_TEXTURE_MIN_FILTER, gl::GL_NEAREST);
        texture->setParameter(gl::GL_TEXTURE_MAG_FILTER, gl::GL_NEAREST);
        texture->setParameter(gl::GL_TEXTURE_WRAP_S, gl::GL_MIRRORED_REPEAT);

        texture->image1D(0, gl::GL_RGBA32F, size, 0, gl::GL_RGB, gl::GL_FLOAT, ssaoKernel(size).data());

        return texture;
    }

    globjects::Texture* ssaoNoiseTexture(unsigned int size)
    {
        auto texture = new globjects::Texture(gl::GL_TEXTURE_2D);
        texture->setParameter(gl::GL_TEXTURE_MIN_FILTER, gl::GL_NEAREST);
        texture->setParameter(gl::GL_TEXTURE_MAG_FILTER, gl::GL_NEAREST);
        texture->setParameter(gl::GL_TEXTURE_WRAP_S, gl::GL_MIRRORED_REPEAT);
        texture->setParameter(gl::GL_TEXTURE_WRAP_T, gl::GL_MIRRORED_REPEAT);

        texture->image2D(0, gl::GL_RGBA32F, glm::ivec2(size), 0, gl::GL_RGB, gl::GL_FLOAT, ssaoNoise(size).data());

        return texture;
    }

    const unsigned int kernelSize = 16;
    const unsigned int noiseSize = 128;
}

Text3dPostprocessingStage::Text3dPostprocessingStage()
{
    addInput("color", color);
    addInput("normal", normal);
    addInput("depth", depth);
    addInput("viewport", viewport);
    addInput("camera", camera);
    addInput("projection", projection);
}

Text3dPostprocessingStage::~Text3dPostprocessingStage()
{
}

void Text3dPostprocessingStage::initialize()
{
    static const auto shaderPath = gloperate::dataPath() + "/gloperate-text/shaders/postprocessing.frag";

    m_quad = new gloperate::ScreenAlignedQuad(
        globjects::Shader::fromFile(GLenum::GL_FRAGMENT_SHADER, shaderPath));        

    m_quad->program()->setUniform("colorTexture", 0);
    m_quad->program()->setUniform("normalTexture", 1);
    m_quad->program()->setUniform("depthTexture", 2);
    m_quad->program()->setUniform("kernelTexture", 3);
    m_quad->program()->setUniform("noiseTexture", 4);

    m_noise = ssaoNoiseTexture(noiseSize);
}

void Text3dPostprocessingStage::process()
{
    m_kernel = ssaoKernelTexture(kernelSize);

    auto FBO = globjects::Framebuffer::defaultFBO();
    FBO->bind();

    glClear(GL_DEPTH_BUFFER_BIT);

    color.data()->bindActive(0);
    normal.data()->bindActive(1);
    depth.data()->bindActive(2);
    m_kernel->bindActive(3);
    m_noise->bindActive(4);

    m_quad->program()->setUniform("projection", projection.data()->projection());
    m_quad->program()->setUniform("projectionInverted", projection.data()->projectionInverted());
    m_quad->program()->setUniform("normalMatrix", camera.data()->normal());
    m_quad->program()->setUniform("farZ", projection.data()->zFar());
    m_quad->program()->setUniform("samplerSizes", glm::vec4(kernelSize, 1.0f / kernelSize, noiseSize, 1.0f / noiseSize));

    m_quad->draw();

    FBO->unbind();
}
