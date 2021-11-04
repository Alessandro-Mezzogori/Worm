#pragma once

#include <thread>
#include "Worm/Events/Event.h"
#include "Worm/DataStructures/QueueMT.h"

namespace Worm {
	class EventThread : public std::thread {
	public:
		EventThread(std::function<void()> handler) : std::thread(handler)
		{
		}

		inline void QueueEvent(BaseEvent* e) { m_Queue.enqueue(std::shared_ptr<BaseEvent>(e)); };
		inline void QueueEvent(std::shared_ptr<BaseEvent> e) { m_Queue.enqueue(e); }
		inline std::shared_ptr<BaseEvent> PopEvent() { return m_Queue.dequeue(); }
	private:
		mt::QueueMT<std::shared_ptr<BaseEvent>> m_Queue;
	};
}