#include "wormpch.h"
#include "WindowsWindow.h"

#include "GLFW/glfw3.h"

#include "Worm/Core/Events/Event.h"
#include "Worm/Core/Events/ApplicationEvents.h"
#include "Worm/Core/Events/WindowEvents.h"
#include "Worm/Core/Events/MouseEvents.h"
#include "Worm/Core/Events/KeyEvents.h"

namespace Worm::Platform {
	static bool s_GLFWInitialized = false;
	
	static void glfwErrorCallback(int error, const char* description) {
		WORM_LOG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		WORM_LOG_CORE_INFO("Creating Window {0} Width: {1} Height {2}", m_Data.Title, m_Data.Width, m_Data.Height);

		// Temporary
		if (!s_GLFWInitialized)
		{
			// TODO glfw terminate on system shutdown
			int success = glfwInit();
			
			WORM_CORE_ASSERT(success == GLFW_TRUE, "Could not initialize GLFW");
			glfwSetErrorCallback(Worm::Platform::glfwErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//
		//	Input initialization
		//

		m_Input.reset(new WindowsInput());

		//
		//	Event Implementation
		//

		// Keyboard
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
			
			switch (action) {
				case GLFW_PRESS:
				{
					data->EventCallback(std::shared_ptr<BaseEvent>(new KeyPressedEvent(key, mods)));
					break;
				}
				case GLFW_RELEASE:	
				{
					data->EventCallback(std::shared_ptr<BaseEvent>(new KeyReleasedEvent(key, mods)));
					break;
				}
				case GLFW_REPEAT:	
				{
					
					data->EventCallback(std::shared_ptr<BaseEvent>(new KeyPressedEvent(key, mods, true)));
					break;
				}
			}

		});

		glfwSetCharModsCallback(m_Window, [](GLFWwindow* window, unsigned int c, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			
			data->EventCallback(std::shared_ptr<BaseEvent>(new KeyTypedEvent(c, mods)));
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS:
				{
					data->EventCallback(std::shared_ptr<BaseEvent>(new MousePressedEvent(button, mods)));
					break;
				}
				case GLFW_RELEASE:
				{
					data->EventCallback(std::shared_ptr<BaseEvent>(new MouseReleasedEvent(button, mods)));
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
			
			data->EventCallback(std::shared_ptr<BaseEvent>(new MouseScrolledEvent(xOffset, yOffset)));
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			
			data->EventCallback(std::shared_ptr<BaseEvent>(new CursorMovedEvent(xpos, ypos)));
		});	

		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			if (entered == GL_TRUE) {
				data->EventCallback(std::shared_ptr<BaseEvent>(new CursorEnterEvent()));
			}
			else {
				data->EventCallback(std::shared_ptr<BaseEvent>(new CursorExitEvent()));
			}
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			
			data->EventCallback(std::shared_ptr<BaseEvent>(new WindowResizedEvent((unsigned int)width, (unsigned int)height)));
		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		
			if (focused == GL_TRUE)
			{
				data->EventCallback(std::shared_ptr<BaseEvent>(new WindowFocusedEvent()));
			}
			else {
				data->EventCallback(std::shared_ptr<BaseEvent>(new WindowUnfocusedEvent()));
			}
		});

		glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow* window) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->EventCallback(std::shared_ptr<BaseEvent>(new WindowRefreshedEvent()));
		});

		glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconify) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			if (iconify == GL_TRUE)
			{
				data->EventCallback(std::shared_ptr<BaseEvent>(new WindowMinimizedEvent()));
			}
			else {
				data->EventCallback(std::shared_ptr<BaseEvent>(new WindowUnminimizedEvent()));
			}
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xPos, int yPos) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->EventCallback(std::shared_ptr<BaseEvent>(new WindowMovedEvent(xPos, yPos)));
		});

		glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int maximized) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			if (maximized == GL_TRUE)
			{
				WindowMaximizedEvent event;
				data->EventCallback(std::shared_ptr<BaseEvent>(new WindowMaximizedEvent()));
			}
			else {
				data->EventCallback(std::shared_ptr<BaseEvent>(new WindowUnmaximizedEvent()));
			}
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
			WindowData *data = (WindowData*) glfwGetWindowUserPointer(window);
			data->EventCallback(std::shared_ptr<BaseEvent>(new WindowClosedEvent()));
		});

		glfwSetDropCallback(m_Window, [](GLFWwindow* window, int pathCount, const char* paths[]) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->EventCallback(std::shared_ptr<BaseEvent>(new PathDroppedEvent(pathCount, paths)));
		});
	}

	uint32_t WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	uint32_t WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		glfwSwapInterval(enabled ? 1 : 0);
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}