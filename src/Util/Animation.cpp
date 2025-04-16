#include "Util/Animation.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

namespace Util {
Animation::Animation(const std::vector<std::string> &paths, bool play,
                     std::size_t interval, bool looping, std::size_t cooldown)
    : m_State(play ? State::PLAY : State::PAUSE),
      m_Interval(interval),
      m_Looping(looping),
      m_Cooldown(cooldown) {
    m_Frames.reserve(paths.size());
    for (const auto &path : paths) {
        m_Frames.push_back(std::make_shared<Util::Image>(path));
    }
}

void Animation::SetCurrentFrame(std::size_t index) {
    m_Index = index;
    if (m_State == State::ENDED || m_State == State::COOLDOWN) {
        /*this make sure if user setframe on ENDED/COOLDOWN, will play from
         * where you set the frame*/
        m_IsChangeFrame = true;
    }
}

void Animation::Draw(const Core::Matrices &data) {
    m_Frames[m_Index]->Draw(data);
    Update();
}

void Animation::Play() {
    if (m_State == State::PLAY)
        return;
    if (m_State == State::ENDED || m_State == State::COOLDOWN) {
        m_Index = m_IsChangeFrame ? m_Index : 0;
        m_IsChangeFrame = false;
    }
    m_State = State::PLAY;
}

void Animation::Pause() {
    if (m_State == State::PLAY || m_State == State::COOLDOWN) {
        m_State = State::PAUSE;
    }
}

void Animation::SetFrameRange(std::size_t start, std::size_t end) {
    if (start >= m_Frames.size() || end >= m_Frames.size() || start > end) {
        throw std::out_of_range("Invalid frame range");
    }
    m_FrameStart = start;
    m_FrameEnd = end;
    m_Index = m_FrameStart; // 重置到範圍的起始幀
}

void Animation::Update() {
    unsigned long nowTime = Util::Time::GetElapsedTimeMs();
    if (m_State == State::PAUSE || m_State == State::ENDED) {
        LOG_TRACE("[ANI] is pause");
        return;
    }

    if (m_State == State::COOLDOWN) {
        if (nowTime >= m_CooldownEndTime) {
            Play();
        }
        return;
    }

    m_TimeBetweenFrameUpdate += Util::Time::GetDeltaTimeMs();
    auto updateFrameCount =
        static_cast<unsigned int>(m_TimeBetweenFrameUpdate / m_Interval);
    if (updateFrameCount <= 0)
        return;

    m_Index += updateFrameCount;
    m_TimeBetweenFrameUpdate = 0;

    if (m_Index > m_FrameEnd) { // 限制在範圍內
        if (m_Looping) {
            m_CooldownEndTime = nowTime + m_Cooldown;
            m_Index = m_FrameStart; // 從範圍起始幀重新播放
        } else {
            m_State = State::ENDED;
            m_Index = m_FrameEnd; // 停留在範圍的最後一幀
        }
    }
}
} // namespace Util
