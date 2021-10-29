#pragma once

#include "Worm/Core/Input.h"

namespace Worm::Platform{

	class WindowsInput : public Input
	{
	public:
		virtual bool IsKeyPressed(int keycode) const override;
		virtual bool IsMouseButtonPressed(int button) const override;
		virtual std::pair<double, double> GetMousePosition() const override;
	};

}

