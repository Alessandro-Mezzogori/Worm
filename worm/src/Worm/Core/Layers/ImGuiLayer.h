#pragma once

#include "Worm/Core/ApplicationLayer.h"

#include "Worm/Events/ApplicationEvents.h"
#include "Worm/Events/KeyEvents.h"
#include "Worm/Events/MouseEvents.h"

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


