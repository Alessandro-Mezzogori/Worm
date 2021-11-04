#pragma once

#include "Worm/Events/Event.h"

namespace Worm {
	class Layer
	{
	public:
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnEvent(Shared<BaseEvent> e) {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
	};
}