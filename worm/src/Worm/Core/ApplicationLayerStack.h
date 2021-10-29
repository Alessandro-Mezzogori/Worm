#pragma once

#include "ApplicationLayer.h"

#include <deque>

namespace Worm {
	class LayerStack{
	public:
		~LayerStack() {
			for (Layer* layer : m_Layers){
				delete layer;
			}
		}

		void PushLayer(Layer* layer) { 
			layer->OnAttach();
			m_Layers.push_back(layer); 
		}
		void PushOverlay(Layer* overlay) { 
			overlay->OnAttach();
			m_Layers.push_front(overlay); 
		}

		Layer* PopLayer() { 
			Layer* l = m_Layers.back(); 
			m_Layers.pop_back();
			
			l->OnDetach();

			return l; 
		}

		Layer* PopOverlay() { 
			Layer* l = m_Layers.front(); 
			m_Layers.pop_front();
			
			l->OnDetach();

			return l; 
		}

		std::deque<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::deque<Layer*>::iterator end() { return m_Layers.end(); }
		
		std::deque<Layer*>::const_iterator cbegin() { return m_Layers.cbegin(); }
		std::deque<Layer*>::const_iterator cend() { return m_Layers.cend(); }

		std::deque<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::deque<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::deque<Layer*>::const_reverse_iterator crbegin() { return m_Layers.crbegin(); }
		std::deque<Layer*>::const_reverse_iterator crend() { return m_Layers.crend(); }

	private:
		std::deque<Layer*> m_Layers;
	};
}