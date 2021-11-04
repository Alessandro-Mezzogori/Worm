#pragma once

#include "Worm/Core/Core.h"
#include "Worm/Events/Event.h"
#include "Input.h"

namespace Worm {
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(
			const std::string& title = "Worm Engine",
			unsigned int width = 1280,
			unsigned int height = 720
		) : Title(title), Width(width), Height(height)
		{
		}
	};

	//
	// Interface for Application Windows on all platforms
	//
	class Window {
	public:
		using EventCallbackFn = std::function<void(Shared<BaseEvent>)>;
	public:
		virtual ~Window() {}

		virtual unsigned int GetWidth()  const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void OnUpdate() = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual const Input* GetNativeInput() const = 0;
	public:
		static Unique<Window> Create();
	};
}