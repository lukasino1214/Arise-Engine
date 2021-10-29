//
// Created by lukas on 03.10.21.
//

#ifndef ARISE_ENGINE_OPENGLSHADER_H
#define ARISE_ENGINE_OPENGLSHADER_H

#include "../Shader.h"
#include <unordered_map>
#include <glad/glad.h>

namespace Engine {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetInt(const std::string& name, int value) override;
        virtual void SetUInt(const std::string& name, uint value) override;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
        virtual void SetFloat(const std::string& name, float value) override;
        virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
        virtual void SetMat3(const std::string& name, const glm::mat3& value) override;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
    private:
        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

        void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
    private:
        uint32_t m_RendererID;
    };
}


#endif //ARISE_ENGINE_OPENGLSHADER_H
