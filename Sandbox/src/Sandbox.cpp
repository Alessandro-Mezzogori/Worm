#include "Worm.h"

#include <iostream>

#include "Worm/Rendering/VertexArray.h"
#include "Worm/Rendering/UniformBuffer.h"
#include "Worm/Rendering/Shader.h"
#include "Worm/Rendering/Buffers.h"
#include "Worm/Rendering/Texture.h"

#include "Worm/Rendering/OrthographicCamera.h"

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

	//Shared<VertexArray> m_VertexArray;
	Shared<Shader> m_Shader;
	Shared<Texture> m_Texture;
	Shared<UniformBuffer> m_UniformBuffer;

	RenderingFrame m_Frame;
	RenderingFrame m_Frame2;

	RenderingBatchElement m_Element;
	RenderingBatchElement m_Element2;

	Shared<Camera> m_Camera;

	std::vector<float> data = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // front lower left
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // front lower right
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // front upper right
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // front upper left
	};

	std::vector<uint32_t> indices = {
		0, 1, 2, 2, 3, 0,
	};

	ExampleLayer()
	{
		m_Camera = CreateSharedResource<OrtographicCamera>(Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight());
		m_Camera->Move({ -3.0f, 0.0f, 0.0f });

		m_Element = { data.data(), indices.data(), data.size() * sizeof(float), indices.size(), BufferLayout({ { ShaderType::FLOAT3, "aPos" }, {ShaderType::FLOAT2, "aTex"} }) };
		// m_Element2 = { data2.data(), indices.data(), sizeof(data2), indices.size(), m_Element.Layout };

		m_Frame = RenderingFrame({ 0.0f, 0.0f, 0.5f, 1.0f });
		m_Frame2 = RenderingFrame(ViewportUtils::GetHorizontalComplementaryViewport(m_Frame.renderingViewport));

		// Shaders 

		const char* vertexShaderSource = R"(#version 430 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec2 aTex;

			out vec3 Position;
			out vec2 TexCoords;

			uniform mat4 u_CameraMatrix;
		
			void main()
			{
				TexCoords = aTex;
				// Position = vec3(u_CameraMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0));
				Position = aPos;				
				gl_Position = vec4(Position, 1.0f);
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
		static const float blue[] = { 0.0f, 0.0f, 1.0f };
		static const float red[] = { 1.0f, 0.0f, 0.0f };

		Renderer::BeginScene(Environment(), m_Camera.get(), m_Shader.get());
		
		m_Shader->Activate();
		m_UniformBuffer->Bind();
		m_Shader->LoadInt("texture0", 1);
		
		Renderer::Submit(m_Element);
		// Renderer::Submit(m_Element2);

		RenderCommand::ClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::ClearFrame();
		m_UniformBuffer->SetData((void*) red, sizeof(red));

		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
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