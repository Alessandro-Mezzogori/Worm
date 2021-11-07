#pragma once

#include "Window.h"
#include "Worm/Events/Event.h"
#include "Worm/Events/WindowEvents.h"

#include "Worm/Core/ApplicationLayerStack.h"
#include "Worm/Core/Layers/ImGuiLayer.h"

#include "Worm/Events/EventThread.h"

#include "Worm/Rendering/RenderingAPIController.h"

namespace Worm {
	//
	//	Interface for the given application class
	//
	class Application
	{
	public:
		Application();
		virtual ~Application() {};

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		//	Main Application Loop 
		virtual void Run();  

		inline static const Unique<Window>& GetWindow() { return s_Instance->m_Window; }
		inline static const ImGuiLayer* GetImGuiLayer() { return s_Instance->m_ImGuiLayer; }
		inline static RenderingAPI::API GetAPI() { return RenderingAPIController::GetAPI(); }
	private:
		//	Events Callback
		bool OnWindowClose(WindowClosedEvent& e);

		// Events thread functions
		void QueueEvent(Shared<BaseEvent> e);
		void EventThreadLoop();
	private:
		bool m_Running;

		LayerStack m_LayerStack;
		Unique<Window> m_Window;
		Unique<EventThread> m_EventThread;

		ImGuiLayer* m_ImGuiLayer; // Owned by m_LayerStack
	private:
		static Application* s_Instance;
	};

	//
	// Hook into the framework to use the implemented application ( MUST BE IMPLEMENTED )
	//
	extern Application* CreateApplication();
}