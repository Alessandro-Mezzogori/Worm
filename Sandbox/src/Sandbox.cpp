#include "Worm.h"

#include <iostream>

#include "Worm/Rendering/VertexArray.h"
#include "Worm/Rendering/UniformBuffer.h"
#include "Worm/Rendering/Shader.h"
#include "Worm/Rendering/Buffers.h"
#include "Worm/Rendering/Texture.h"

#include "imgui/imgui.h"


using namespace Worm;

class TestEvent : public Worm::Event<>
{
public:
	virtual const std::string ToString() const override
	{
		return "TestEvent";
	}
};

class ExampleLayer : public Worm::Layer
{
public:
	unsigned int shaderProgram;

	Shared<VertexArray> m_VertexArray;
	Shared<Shader> m_Shader;
	Shared<Texture> m_Texture;
	Shared<UniformBuffer> m_UniformBuffer;


	RenderingFrame m_Frame;
	RenderingFrame m_Frame2;

	ExampleLayer()
	{
		float data[] = {
			0.5f, 0.5f, 0.0, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0, 1.0f, 0.0f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3,
		};

		m_Frame = RenderingFrame({ 0.0f, 0.0f, 0.5f, 1.0f });
		m_Frame2 = RenderingFrame(ViewportUtils::GetHorizontalComplementaryViewport(m_Frame.renderingViewport));

		m_VertexArray = VertexArray::Create();
		m_VertexArray->Bind();

		Shared<VertexBuffer> vbo = VertexBuffer::Create();
		vbo->Bind();
		vbo->SetData(data, sizeof(data));
		vbo->SetLayout(BufferLayout({ { ShaderType::FLOAT3, "aPos" }, {ShaderType::FLOAT2, "aTex"}}));

		Shared<IndexBuffer> ibo = IndexBuffer::Create();
		ibo->Bind();
		ibo->SetData(indices, sizeof(indices)/sizeof(uint32_t));

		m_VertexArray->AddVertexBuffer(vbo);
		m_VertexArray->SetIndexBuffer(ibo);

		// Shaders 

		const char* vertexShaderSource = R"(#version 430 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec2 aTex;

			out vec3 Position;
			out vec2 TexCoords;
		
			void main()
			{
				TexCoords = aTex;
				Position = aPos;
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			}
		)";
		const char* fragmentShaderSource = R"(#version 430 core
			out vec4 FragColor;

			in vec3 Position;
			in vec2 TexCoords;

			uniform sampler2D texture0;

			layout(std140, binding = 1) uniform TestBlock
			{
				vec3 u_Color;
			};

			void main()
			{
			   FragColor = texture(texture0, TexCoords)*vec4(u_Color, 1.0f);
			}
		)";

		m_Shader = Shader::Create(vertexShaderSource, fragmentShaderSource);
		m_UniformBuffer = UniformBuffer::Create();
		m_UniformBuffer->Bind();
		uint32_t binding = m_Shader->GetUniformBlockBinding("TestBlock");
		m_UniformBuffer->SetBindingPoint(binding);

		m_Texture = Texture::Create("assets/textures/wood_container.jpg");
		m_Texture->Bind(1);
	}

	virtual void OnEvent(std::shared_ptr<Worm::BaseEvent> e) override {

	}

	virtual void OnUpdate() override 
	{
		Renderer::BeginScene(Environment(), Camera());
		m_Shader->Activate();
		m_UniformBuffer->Bind();
		m_Shader->LoadInt("texture0", 1);

		m_VertexArray->Bind();

		Renderer::SetActiveRenderingFrame(m_Frame);
		RenderCommand::ClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::ClearFrame();
		
		const float blue[] = { 0.0f, 0.0f, 1.0f};
		m_UniformBuffer->SetData((void*)blue, sizeof(blue));
		Renderer::Submit(*m_VertexArray);

		Renderer::SetActiveRenderingFrame(m_Frame2);
		RenderCommand::ClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::ClearFrame();

		const float red[] = { 1.0f, 0.0f, 0.0f };
		m_UniformBuffer->SetData((void*) red, sizeof(red));
		Renderer::Submit(*m_VertexArray);

		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Text("Layer render");
	}
};

class TestApplication : public Worm::Application
{
public:
	TestApplication() : Application()
	{
		PushLayer(new ExampleLayer());
 	}

	~TestApplication()
	{

	}
private:

};

Worm::Application* Worm::CreateApplication() { return new TestApplication(); }