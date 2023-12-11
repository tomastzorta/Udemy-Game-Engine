//
// Created by Tomas Tzorta on 11/12/2023.
//

#include "LabyrinthFramework/TimeManager.h"

namespace labyrinth_engine
{
    Unique<TimeManager> TimeManager::m_timeManager{nullptr};

    Timer::Timer(Weak<Object> a_weakObject, std::function<void()> a_function, float a_time, bool a_repeat)
        : m_function{a_weakObject, a_function}
        , m_time{a_time}
        , m_bRepeat{a_repeat}
        , m_currentTime{0.0f}
        , m_bIsFinished{false}
    {

    }

    TimeManager::TimeManager()
        : m_timers{}
    {

    }
    unsigned int TimeManager::m_currentIndex = 0;

    void Timer::Update(float a_deltaTime)
    {
        if (IsFinished()) return;

        m_currentTime += a_deltaTime;

        if (m_currentTime >= m_time)
        {
            m_function.second();
            if (m_bRepeat)
            {
                m_currentTime = 0.0f;
            }
            else
            {
                SetToFinish();
            }
        }
    }

    bool Timer::IsFinished() const
    {
        return m_bIsFinished || m_function.first.expired() || m_function.first.lock()->IsPendingKill();
    }


    void TimeManager::UpdateTimerManager(const float a_deltaTime)
    {
        for (auto i = m_timers.begin(); i != m_timers.end();)
        {
            if (i->second.IsFinished())
            {
                i = m_timers.erase(i);
            }
            else
            {
                i->second.Update(a_deltaTime);
                ++i;
            }
        }
    }

    void TimeManager::RemoveTimer(const unsigned int a_index)
    {
        auto i = m_timers.find(a_index);

        if (i != m_timers.end())
        {
            i->second.SetToFinish();
        }
    }

    TimeManager& TimeManager::GetInstance()
    {
        if (!m_timeManager)
        {
            m_timeManager = Unique<TimeManager>(new TimeManager{});
        }

        return *m_timeManager;
    }
}
