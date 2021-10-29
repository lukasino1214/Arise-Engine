//
// Created by lukas on 02.10.21.
//

#include <glad/glad.h>

#include "OpenGLRendererAPI.h"

namespace Engine {
    void OpenGLRendererAPI::Init() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> &vertexArray) {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        vertexArray->Unbind();
    }

    void OpenGLRendererAPI::Draw(const Ref<VertexArray> &vertexArray) {
        vertexArray->Bind();
        glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetVertexBuffer()->GetSize());
        vertexArray->Unbind();
    }
}