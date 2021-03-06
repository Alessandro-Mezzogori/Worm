#include "Worm.h"

#include <iostream>


#include "Worm/Platform/RenderingApi/OpenGL/OpenGLBuffers.h"
#include "Worm/Platform/RenderingApi/OpenGL/OpenGLVertexArray.h"
#include "Worm/Platform/RenderingApi/OpenGL/OpenGLShader.h"

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

		//Renderer::UseRenderingFrame(RenderingFrame(RenderingAPIController::API::OPENGL, { 0.0f, 0.0f, 1.0f, 1.0f }));

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

		const char* vertexShaderSource = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos;

			out vec3 Position;
		
			void main()
			{
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
				Position = aPos;
			}
		)";
		const char* fragmentShaderSource = R"(#version 330 core
			out vec4 FragColor;

			in vec3 Position;

			void main()
			{
			   FragColor = vec4(Position, 1.0f);
			}
		)";

		m_Shader = CreateSharedResource<OpenGLShader>(vertexShaderSource, fragmentShaderSource);
	}

	virtual void OnEvent(std::shared_ptr<Worm::BaseEvent> e) override {

	}

	virtual void OnUpdate() override 
	{
		Renderer::ClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		Renderer::ClearFrame();

		m_Shader->Activate();
		m_VertexArray->Bind();

		Renderer::RenderVertexArray(*m_VertexArray);
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