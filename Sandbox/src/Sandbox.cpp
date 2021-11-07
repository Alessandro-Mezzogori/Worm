#include "Worm.h"

#include <iostream>

#include "Worm/Platform/RenderingApi/OpenGL/OpenGLBuffers.h"
#include "Worm/Platform/RenderingApi/OpenGL/OpenGLVertexArray.h"
#include "Worm/Platform/RenderingApi/OpenGL/OpenGLShader.h"
#include "Worm/Platform/RenderingApi/OpenGL/OpenGLUniformBuffer.h"

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

		m_VertexArray = Worm::CreateSharedResource<OpenGLVertexArray>();
		m_VertexArray->Bind();

		Shared<VertexBuffer> vbo = Worm::CreateSharedResource<OpenGLVertexBuffer>();
		vbo->Bind();
		vbo->SetData(data, sizeof(data));
		vbo->SetLayout(BufferLayout({ { ShaderType::FLOAT3, "aPos" }, {ShaderType::FLOAT2, "aTex"}}));

		Shared<IndexBuffer> ibo = Worm::CreateSharedResource<OpenGLIndexBuffer>();
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
			   FragColor = texture(texture0, TexCoords);
			}
		)";

		m_Shader = CreateSharedResource<OpenGLShader>(vertexShaderSource, fragmentShaderSource);

		m_Texture = Texture::Create("assets/textures/wood_container.jpg");
		m_Texture->Bind(1);
	}

	virtual void OnEvent(std::shared_ptr<Worm::BaseEvent> e) override {

	}

	virtual void OnUpdate() override 
	{
		Renderer::BeginScene(Environment(), Camera());

		RenderCommand::ClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::ClearFrame();
		m_Shader->Activate();
		m_Shader->LoadInt("texture0", 1);
		m_VertexArray->Bind();
		Renderer::Submit(*m_VertexArray);

		RenderCommand::ClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::ClearFrame();
		m_Shader->Activate();
		// m_Shader->LoadFloat3("u_Color", { 0.0f, 1.0f, 0.0f });
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