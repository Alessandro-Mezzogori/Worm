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
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // back lower left
		1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // back lower right 
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // back upper right
		0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // back upper left
	};

	std::vector<uint32_t> indices = {
		0, 1, 2, 2, 3, 0,
		1, 5, 6, 6, 2, 1,
		5, 4, 7, 7, 6, 5,
		4, 0, 3, 3, 7, 4
	};

	const BufferLayout m_Layout = BufferLayout({ { ShaderType::FLOAT3, "aPos" }, {ShaderType::FLOAT2, "aTex"} });

	ExampleLayer()
	{
		m_Camera = Shared<OrtographicCamera>(new OrtographicCamera(Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight(), { 0.0f, 1.0f, 2.0f }, { 0.0f, 0.5f, 0.0f }));

		m_Element = { data.data(), indices.data(), data.size() * sizeof(float), indices.size() };
		// m_Element2 = { data2.data(), indices.data(), sizeof(data2), indices.size(), m_Element.Layout };

		m_Frame = RenderingFrame({ 0.0f, 0.0f, 0.5f, 1.0f });
		m_Frame2 = RenderingFrame(ViewportUtils::GetHorizontalComplementaryViewport(m_Frame.renderingViewport));

		// Shaders 

		const char* vertexShaderSource = R"(#version 430 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec2 aTex;

			out vec2 TexCoords;

			uniform mat4 u_CameraMatrix;
		
			void main()
			{
				TexCoords = aTex;
				gl_Position = u_CameraMatrix * vec4(aPos, 1.0);
			}
		)";
		const char* fragmentShaderSource = R"(#version 430 core
			out vec4 FragColor;

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

	bool CameraMovement(KeyPressedEvent e){
		KeyCode keycode = e.GetKeyCode();
	
		switch(keycode){
			case Key::A: m_Camera->Move({ -1.0f, 0.0f, 0.0f }); break;
			case Key::D: m_Camera->Move({ 1.0f, 0.0f, 0.0f }); break;
			case Key::W: m_Camera->Move({ 0.0f, 0.0f, -1.0f}); break;
			case Key::S: m_Camera->Move({ 0.0f, 0.0f, 1.0f}); break;
			case Key::Q: m_Camera->Rotate(-40.0f, 0.0f); break;
			case Key::E: m_Camera->Rotate(40.0f, 0.0f); break;
			case Key::F: m_Camera->Rotate(0.0f, 40.0f); break;
			case Key::G: m_Camera->Rotate(0.0f, -40.0f); break;
		}

		return true;
	}


	virtual void OnEvent(Shared<Worm::BaseEvent> e) override {
		Worm::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(Worm::BIND_METHOD_CALLBACK<bool, KeyPressedEvent, ExampleLayer>(this, &ExampleLayer::CameraMovement));
	}

	virtual void OnUpdate() override 
	{
		static const float blue[] = { 0.0f, 0.0f, 1.0f };
		static const float red[] = { 1.0f, 0.0f, 0.0f };

		RenderCommand::EnableDepthTest(m_DepthTest);
		Renderer::BeginScene(m_Camera.get(), m_Shader.get(), m_Layout);
		
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

	bool m_DepthTest;

	virtual void OnImGuiRender() override {
		ImGui::Checkbox("Depth Test", &m_DepthTest);
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