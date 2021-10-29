#pragma once

#include "Worm/Core/ApplicationLayer.h"

#include "Worm/Core/Events/ApplicationEvents.h"
#include "Worm/Core/Events/KeyEvents.h"
#include "Worm/Core/Events/MouseEvents.h"

namespace Worm {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() = default;

		void Begin();
		void End();
		
		virtual void OnAttach() override ;
		virtual void OnDetach() override ;

		virtual void OnEvent(Shared<BaseEvent> e) override ;

		void SetDarkThemeColors();
	};
}


