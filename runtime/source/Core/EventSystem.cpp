#include "Core/EventSystem.h"

#include <algorithm>

namespace ERUNTIME_NAMESPACE
{
    EventBus& EventBus::Instance()
    {
        static EventBus s_Bus;
        return s_Bus;
    }

    void EventBus::SetImmediateMode(bool immediate)
    {
        m_ImmediateMode = immediate;
    }

    void EventBus::AddListener(EventListener* listener)
    {
        m_Listeners.push_back(listener);
    }

    void EventBus::RemoveListener(EventListener* listener)
    {
      auto it = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
      if (it != m_Listeners.end()) {
        m_Listeners.erase(it);
        }
        else {
            /* TODO: Logging here (Trying to remove unexisting listener from event bus) */
        }
    }

    void EventBus::PublishEvent(const Event& event)
    {
        if(m_ImmediateMode)
        {
            for(auto listener : m_Listeners)
            {
                listener->OnEvent(event);
            }
        }
        else
        {
            std::lock_guard<std::mutex> lock(m_Sync);
            m_EventQueue.push(Scope<Event>(event.Clone()));
        }
    }

    void EventBus::ProcessEvents()
    {
        if(m_ImmediateMode) return;

        std::queue<Scope<Event>> current_events;

        {
            std::lock_guard<std::mutex> lock(m_Sync);
            std::swap(current_events, m_EventQueue);
        }

        while(!current_events.empty())
        {
            auto& event = *current_events.front();

            for(auto listener : m_Listeners)
            {
                listener->OnEvent(event);
            }

            current_events.pop();
        }
    }
}