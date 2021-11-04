#pragma once

#include <utility>
#include "Worm/Events/Codes.h"

namespace Worm {
	class Input {
	public:
		//
		// Input Interface methods
		//
		inline virtual bool IsKeyPressed(int keycode) const = 0;
		inline virtual bool IsMouseButtonPressed(int button) const = 0;
		inline virtual std::pair<double, double> GetMousePosition() const = 0;
		
		inline double GetMouseX() const { return GetMousePosition().first; }
		inline double GetMouseY() const { return GetMousePosition().second; }
	};
}