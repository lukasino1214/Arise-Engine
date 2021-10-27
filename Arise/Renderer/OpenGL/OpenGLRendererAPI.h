//
// Created by lukas on 02.10.21.
//

#ifndef ARISE_OPENGLRENDERERAPI_H
#define ARISE_OPENGLRENDERERAPI_H

#include "../RendererAPI.h"

#include <memory>

namespace Engine {
    class OpenGLRendererAPI : public RendererAPI {
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
        virtual void Draw(const Ref<VertexArray>& vertexArray) override;
    };
}


#endif //ARISE_OPENGLRENDERERAPI_H
