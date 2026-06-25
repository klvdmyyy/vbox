#pragma once

#include "Core/Memory.h"

#include <mutex>
#include <queue>
#include <type_traits>
#include <vector>

/* Macro to help define event types */
#define DEFINE_EVENT_TYPE(type)                                         \
  static const char* GetStaticType() { return #type; }			\
  virtual const char* GetType() const override { return GetStaticType(); } \
  virtual ::ERUNTIME_NAMESPACE::Event* Clone() const override { return new type(*this); }

namespace ERUNTIME_NAMESPACE
{
    class ERUNTIME_API Event
    {
    public:
        virtual ~Event() = default;

        virtual const char* GetType() const = 0;
        virtual Event* Clone() const = 0;
    };

    class ERUNTIME_API EventListener
    {
    public:
        virtual ~EventListener() = default;
        virtual void OnEvent(const Event& event) = 0;
    };

    class ERUNTIME_API EventDispatcher
    {
    public:
        explicit EventDispatcher(const Event& e) : m_Event(e)
        {
        }

        template<typename T, typename F>
        bool Dispatch(const F& handler)
        {
            static_assert(std::is_base_of<Event, T>::value, "Can't dispatch event. Event type must be derived from core::Event");

            if (m_Event.GetType() == T::GetStaticType())
            {
              handler(static_cast<const T &>(m_Event));
                return true;
            }
            return false;
        }

    private:
        const Event& m_Event;
    };

    class ERUNTIME_API EventBus
    {
    public:
        static EventBus& Instance();

        EventBus(const EventBus&) = delete;
        EventBus& operator=(const EventBus&) = delete;

        void SetImmediateMode(bool immediate);
        void AddListener(EventListener* listener);
        void RemoveListener(EventListener* listener);
        void PublishEvent(const Event& event);
        void ProcessEvents();

    private:
        std::vector<EventListener*> m_Listeners;
        std::queue<Scope<Event>> m_EventQueue;
        std::mutex m_Sync;

        bool m_ImmediateMode = true;

        EventBus() = default;
    };
}