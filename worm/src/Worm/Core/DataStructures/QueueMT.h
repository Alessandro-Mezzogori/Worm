#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace Worm::mt{
	template<typename T>
	class QueueMT
	{
	public:
		QueueMT() : m_Queue(), m_Condition(), m_Mutex()
		{
		}

		void enqueue(T t)
		{
			std::lock_guard lock(m_Mutex);
			m_Queue.push(t);
			m_Condition.notify_one();
		}

		T dequeue()
		{
			std::unique_lock<std::mutex> lock(m_Mutex);

			while (m_Queue.empty())
			{
				// release lock as long as the wait and reaquire it afterwards.
				m_Condition.wait(lock);
			}
			T t = m_Queue.front();
			m_Queue.pop();

			return t;
		}
	private:
		std::condition_variable m_Condition;
		mutable std::mutex m_Mutex;
		std::queue<T> m_Queue;
	};
}

