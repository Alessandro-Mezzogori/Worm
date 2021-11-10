#pragma once

#include <vector>

#include "Worm/Core/Core.h"

#include "Worm/Rendering/VertexArray.h"

namespace Worm{



    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void AddVertexBuffer(Shared<VertexBuffer> buffer) override;
        virtual void SetIndexBuffer(Shared<IndexBuffer> buffer) override;
        virtual void DetachVertexBuffers() override;
        virtual const Shared<IndexBuffer>& GetIndexBuffer() const override;

        virtual void SetBufferLayout(BufferLayout layout) override;
    private:
        unsigned int m_ID;

        BufferLayout m_Layout;
        std::vector<Shared<VertexBuffer>> m_VertexBuffers;
        Shared<IndexBuffer> m_IndexBuffer;

        unsigned int m_LayoutIndex;
    };

}

