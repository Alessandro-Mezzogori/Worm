#include "wormpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Worm/Core/Application.h"

bool Worm::Platform::WindowsInput::IsKeyPressed(int keycode) const
{
    return glfwGetKey((GLFWwindow*)Application::GetWindow()->GetNativeWindow(), keycode) == GLFW_PRESS;
}

bool Worm::Platform::WindowsInput::IsMouseButtonPressed(int button) const
{
    return glfwGetMouseButton((GLFWwindow*)Application::GetWindow()->GetNativeWindow(), button) == GLFW_PRESS;
}

std::pair<double, double> Worm::Platform::WindowsInput::GetMousePosition() const
{
    double xpos, ypos;
    glfwGetCursorPos((GLFWwindow*)Application::GetWindow()->GetNativeWindow(), &xpos, &ypos);

    return { xpos, ypos };
}
