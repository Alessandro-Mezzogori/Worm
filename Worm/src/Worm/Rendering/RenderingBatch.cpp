#include "wormpch.h"
#include "RenderingBatch.h"

#include "Worm/Core/Log.h"
#include "Worm/Core/Application.h"

namespace Worm{
    RenderingBatch::RenderingBatch()
    {
    }

    void RenderingBatch::INIT(BatchSpecification specification)
    {
        // Set the default values for the control attributes
        m_MaxBatchSize = s_DefaultMaxBatchSize;
        m_MaxIndicesCount = s_DefaultMaxIndicesCount;

        m_VertexSize = 0;
        
        // Texture Batching 
        m_MaxTextureSlots = specification.MaxFragmentTextureSlots;
        m_Textures = std::vector<uint32_t>(m_MaxTextureSlots);

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

        // Attach Vertex and index buffer to the array
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->Unbind();
    }

    void RenderingBatch::Begin(BatchInformation info)
    {
        m_VertexArray->Bind();
        m_VertexArray->SetBufferLayout(info.VerticesLayout);
        m_VertexSize = info.VerticesLayout.GetStride();

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
        m_Textures.clear();
    }

    const VertexArray& RenderingBatch::GetVertexArray() const
    {
        return *m_VertexArray;
    }

    void RenderingBatch::AddData(RenderingBatchElement element)
    {
        // Save the indices
        uint32_t correctionOffset = static_cast<uint32_t>(GetUsedSize() / m_VertexSize); // used to compensate the new position inside the vertex buffer
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
