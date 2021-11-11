#pragma once

#include "Worm/Core/Window.h"

#include "Worm/Platform/OS/Windows/WindowsInput.h"

#include "Worm/Rendering/RenderingContext.h"

#include "GLFW/glfw3.h"

namespace Worm::Platform {
	class WindowsWindow : public Window
	{
	public: 
		WindowsWindow(const WindowProperties& data = {});
		~WindowsWindow();

		inline virtual uint32_t GetWidth() const override;
		inline virtual uint32_t GetHeight() const override;
		virtual void OnUpdate() override;

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
		inline virtual const Input* GetNativeInput() const { return m_Input.get(); }
	private:
		virtual void Init(const WindowProperties& data);
		virtual void Shutdown();
	private:
		struct WindowData {
			std::string Title = "";
			unsigned int Width = 0, Height = 0;
			bool VSync = true;

			EventCallbackFn EventCallback;
		};

		GLFWwindow* m_Window;
		WindowData m_Data;

		Unique<RenderingContext> m_Context;
		Unique<WindowsInput> m_Input;

		static uint8_t s_GLFWWindowCount;
	};
}
