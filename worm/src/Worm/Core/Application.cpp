#include "wormpch.h"
#include "Application.h"

#include "Core.h"
#include "Rendering/Renderer.h"

namespace Worm {
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		WORM_CORE_ASSERT(s_Instance == nullptr, "An Instance of application already exists");

		s_Instance = this;

		m_Running = true;
		m_EventThread.reset(new EventThread(BIND_METHOD_CALLBACK<void, Application>(this, &Application::EventThreadLoop)));

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_METHOD_CALLBACK<void, std::shared_ptr<BaseEvent>, Application>(this, &Application::QueueEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		Renderer::INIT();
	}

	void Application::Run() {
		while (m_Running)
		{
			// Update Loop
			for( Layer* layer : m_LayerStack )
				layer->OnUpdate();

			// ImGui Loop
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			// Windows Loop
			m_Window->OnUpdate();
		}

		// Wait for application sub threads to close
		m_EventThread->join();
	}

	void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
	void Application::PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

	void Application::QueueEvent(Shared<BaseEvent> e) {
		m_EventThread->QueueEvent(e);
	}

	void Application::EventThreadLoop(void)
	{
		while(s_Instance->m_Running){
			std::shared_ptr<BaseEvent> e = m_EventThread->PopEvent();

			// Application / Window events
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<WindowClosedEvent>(BIND_METHOD_CALLBACK<bool, WindowClosedEvent&, Application>(this, &Application::OnWindowClose));

			// Propagate events from the first layer trough the last
			for (auto r_itr = m_LayerStack.rbegin(); r_itr != m_LayerStack.rend(); r_itr++)
				(*r_itr)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		m_Running = false;
		return true;
	}
}
