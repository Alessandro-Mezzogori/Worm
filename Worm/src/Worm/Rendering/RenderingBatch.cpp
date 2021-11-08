#include "wormpch.h"
#include "RenderingBatch.h"

#include "Worm/Core/Log.h"
#include "Worm/Core/Application.h"

namespace Worm{
    RenderingBatch::RenderingBatch()
    {
    }

    void RenderingBatch::INIT()
    {
        m_MaxBatchSize = s_DefaultMaxBatchSize;
        m_MaxIndicesCount = s_DefaultMaxIndicesCount;
        m_UsedSize = 0;
        m_UsedIndices = 0;

        m_HasBufferLayout = false;
        
        m_VertexArray = VertexArray::Create();
        m_VertexArray->Bind();

        m_VertexBuffer = VertexBuffer::Create();
        m_IndexBuffer = IndexBuffer::Create();

        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        Allocate();

        m_VertexArray->Unbind();
    }

    void RenderingBatch::Allocate() 
    {
        m_VertexBuffer->Bind();
        m_VertexBuffer->Allocate(m_MaxBatchSize, DrawHint::DYNAMIC);

        m_IndexBuffer->Bind();
        m_IndexBuffer->Allocate(m_MaxIndicesCount, DrawHint::DYNAMIC);
    }

    void RenderingBatch::Clear()
    {
        m_VertexBuffer->Bind();
        m_VertexBuffer->Clear();
        m_IndexBuffer->Bind();
        m_IndexBuffer->Clear();
        
        m_UsedIndices = 0;
        m_UsedSize = 0;
    }

    void RenderingBatch::SetBufferLayout(const BufferLayout& layout)
    {
        m_VertexBuffer->SetLayout(layout);

        // Refresh the auto detecting attribute pointer of the vertex array with the new buffer layout
        m_VertexArray->DetachVertexBuffers();
        m_VertexArray->Bind();
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_HasBufferLayout = true;
    }

    const VertexArray& RenderingBatch::GetVertexArray() const
    {
        WORM_CORE_ASSERT(m_HasBufferLayout, "No BufferLayout has been set for the batch renderer");
        return *m_VertexArray;
    }

    void RenderingBatch::AddData(RenderingBatchElement element)
    {
        if (!m_HasBufferLayout) SetBufferLayout(element.Layout);

        m_VertexBuffer->Bind();
        m_VertexBuffer->SetData(element.Data, element.Size, m_UsedSize);
        m_UsedSize += element.Size;

        m_IndexBuffer->Bind();
        m_IndexBuffer->SetData(element.Indices, element.IndicesCount, m_UsedIndices);
        m_UsedIndices += element.IndicesCount;
    }

    bool RenderingBatch::HasSpace(RenderingBatchElement element) const
    {
        return (m_UsedSize + element.Size <= m_MaxBatchSize) && (m_UsedIndices + element.IndicesCount <= m_MaxIndicesCount);
    }


    size_t RenderingBatch::GetMaximumSize() const
    {
        return m_MaxBatchSize;
    }

    size_t RenderingBatch::GetUsedSize() const
    {
        return m_UsedSize;
    }
}
