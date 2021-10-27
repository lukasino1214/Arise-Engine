//
// Created by lukas on 02.10.21.
//

#ifndef ARISE_ENGINE_OPENGLVERTEXARRAY_H
#define ARISE_ENGINE_OPENGLVERTEXARRAY_H

#include "../VertexArray.h"

namespace Engine {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual const Ref<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffers[0]; }
        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
    private:
        uint32_t m_RendererID;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}


#endif //ARISE_ENGINE_OPENGLVERTEXARRAY_H
