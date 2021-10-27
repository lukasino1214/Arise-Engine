//
// Created by lukas on 02.10.21.
//

#ifndef ARISE_ENGINE_VERTEXARRAY_H
#define ARISE_ENGINE_VERTEXARRAY_H

#include <vector>
#include "Buffer.h"

namespace Engine {
    class VertexArray {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        virtual const Ref<VertexBuffer>& GetVertexBuffer() const = 0;
        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

        static Ref<VertexArray> Create();
    };
}

#endif //ARISE_ENGINE_VERTEXARRAY_H
