#include "wormpch.h"
#include "Window.h"

#include "Worm/Platform/OS/Windows/WindowsWindow.h"
#include "Worm/Platform/OS/Windows/WindowsInput.h"

#include "Core.h"

namespace Worm {
	Unique<Window> Window::Create() {
		// TODO add api to chose between linux / window / mac window
		return CreateUniqueResource<Platform::WindowsWindow>();
	}
}