#include "Worm.h"

#include <iostream>


#include "Worm/Platform/RenderingApi/OpenGL/OpenGLBuffers.h"
#include "Worm/Platform/RenderingApi/OpenGL/OpenGLVertexArray.h"
#include "Worm/Platform/RenderingApi/OpenGL/OpenGLShader.h"
#include "Worm/Platform/RenderingApi/OpenGL/OpenGLUniformBuffer.h"

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
	Shared<Shader> m_Shader2;

	RenderingFrame m_Frame;
	RenderingFrame m_Frame2;

	ExampleLayer()
	{
		float data[] = {
			-0.5, 0.0, 0.0,
			+0.5, 0.0, 0.0,
			0.0, 0.5, 0.0
		};

		unsigned int indices[3] = {
			0, 1, 2
		};

		m_Frame = RenderingFrame({ 0.0f, 0.0f, 0.5f, 1.0f });
		m_Frame2 = RenderingFrame(ViewportUtils::GetHorizontalComplementaryViewport(m_Frame.renderingViewport));

		m_VertexArray = Worm::CreateSharedResource<OpenGLVertexArray>();
		m_VertexArray->Bind();

		Shared<VertexBuffer> vbo = Worm::CreateSharedResource<OpenGLVertexBuffer>();
		vbo->Bind();
		vbo->SetData(data, sizeof(data));
		vbo->SetLayout(BufferLayout({ { ShaderType::FLOAT3, "aPosition" } }));

		Shared<IndexBuffer> ibo = Worm::CreateSharedResource<OpenGLIndexBuffer>();
		ibo->Bind();
		ibo->SetData(indices, sizeof(indices)/sizeof(uint32_t));

		m_VertexArray->AddVertexBuffer(vbo);
		m_VertexArray->SetIndexBuffer(ibo);

		// Shaders 

		const char* vertexShaderSource = R"(#version 430 core
			layout (location = 0) in vec3 aPos;

			out vec3 Position;
		
			void main()
			{
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
				Position = aPos;
			}
		)";
		const char* fragmentShaderSource = R"(#version 430 core
			out vec4 FragColor;

			in vec3 Position;

			layout(std140, binding = 1) uniform TestBlock
			{
				vec3 u_Color;
			};

			void main()
			{
			   FragColor = vec4(u_Color, 1.0f);
			}
		)";

		const char* fragmentShaderSource2 = R"(#version 430 core
			out vec4 FragColor;
			
			in vec3 Position;
			
			void main()
			{
				FragColor = vec4(0.5f, 0.5f, 0.3f, 1.0f);
			}
		)";

		m_Shader = CreateSharedResource<OpenGLShader>(vertexShaderSource, fragmentShaderSource);
		m_Shader2 = CreateSharedResource<OpenGLShader>(vertexShaderSource, fragmentShaderSource2);
	}

	virtual void OnEvent(std::shared_ptr<Worm::BaseEvent> e) override {

	}

	virtual void OnUpdate() override 
	{
		Renderer::BeginScene(Environment(), Camera());

		Renderer::SetActiveRenderingFrame(m_Frame);
		RenderCommand::ClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::ClearFrame();
		m_Shader->Activate();
		m_VertexArray->Bind();
		Renderer::Submit(*m_VertexArray);

		Renderer::SetActiveRenderingFrame(m_Frame2);
		RenderCommand::ClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::ClearFrame();
		m_Shader->Activate();
		m_Shader->LoadUniform("u_Color", { 0.0f, 1.0f, 0.0f });
		m_VertexArray->Bind();
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