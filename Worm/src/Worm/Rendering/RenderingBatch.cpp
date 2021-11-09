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
        // Set the default values for the control attributes
        m_MaxBatchSize = s_DefaultMaxBatchSize;
        m_MaxIndicesCount = s_DefaultMaxIndicesCount;

        m_VertexSize = 0;
        m_HasBufferLayout = false;

        // Allocate memory for the batching on ram
        m_Data = std::vector<char>(m_MaxBatchSize);
        m_DataPtr = m_Data.data();

        m_Indices = std::vector<uint32_t>(m_MaxIndicesCount);
        m_IndicesPtr = m_Indices.data();

        // Create the Vertex Array, VertexBuffer and IndexBuffer 
        m_VertexArray = VertexArray::Create();
        m_VertexArray->Bind();

        m_VertexBuffer = VertexBuffer::Create();
        m_VertexBuffer->Bind();
        m_VertexBuffer->Allocate(m_MaxBatchSize, DrawHint::DYNAMIC);
        
        m_IndexBuffer = IndexBuffer::Create();
        m_IndexBuffer->Bind();
        m_IndexBuffer->Allocate(m_MaxIndicesCount, DrawHint::DYNAMIC); 

        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        m_VertexArray->Unbind();
    }

    void RenderingBatch::Begin()
    {
        Clear();
    }

    void RenderingBatch::End()
    {
        m_VertexBuffer->Bind();
        m_VertexBuffer->SetData(m_Data.data(), GetUsedSize(), 0);

        m_IndexBuffer->Bind();
        m_IndexBuffer->SetData(m_Indices.data(), GetIndicesUsed(), 0);
    }

    void RenderingBatch::Clear()
    {
        // Reset pointers to the first value
        m_DataPtr = m_Data.data();
        m_IndicesPtr = m_Indices.data();
    }

    void RenderingBatch::SetBufferLayout(const BufferLayout& layout)
    {
        m_VertexBuffer->SetLayout(layout);
        m_VertexSize = layout.GetStride();

        // Refresh the auto detecting attribute pointer of the vertex array with the new buffer layout
        m_VertexArray->Bind();
        m_VertexArray->DetachVertexBuffers();
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
        
        // Save the indices
        uint32_t correctionOffset = GetUsedSize() / m_VertexSize; // used to compensate the new position inside the vertex buffer
        for (size_t i = 0; i < element.IndicesCount; i++) {
            m_IndicesPtr[i] = element.Indices[i] + correctionOffset;
        }
        m_IndicesPtr += element.IndicesCount; // update pointer to last elemeent

        // Save vertex data
        memcpy(m_DataPtr, element.Data, element.Size);
        m_DataPtr += element.Size;
    }

    bool RenderingBatch::HasSpace(RenderingBatchElement element) const
    {
        return (GetUsedSize() + element.Size <= m_MaxBatchSize) && (GetIndicesUsed() + element.IndicesCount <= m_MaxIndicesCount);
    }


    size_t RenderingBatch::GetMaximumSize() const
    {
        return m_MaxBatchSize;
    }

    size_t RenderingBatch::GetUsedSize() const
    {
        return (m_DataPtr - m_Data.data());
    }

    size_t RenderingBatch::GetIndicesUsed() const
    {
        return (m_IndicesPtr - m_Indices.data());
    }
}
