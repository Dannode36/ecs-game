#pragma once
#include <vector>
#include "Frame.h"

class Animation
{
public:
	inline Animation() = default;
	inline Animation(const std::vector<Frame>& frames) : m_frames{ frames } {};

	inline void update(float timeDeltaMs);
	inline void reset();

	inline void setCurrentFrame(uint32_t currentFrame);
	inline void setTimeDelta(float timeDelta);

	inline const Frame* getCurrentFrame() const;
	inline uint32_t getCurrentFrameNumber() const;
	inline uint32_t getCurrentTileId() const;
	inline float getTimeDelta() const;

	inline size_t size() const;

private:
	std::vector<Frame> m_frames;
	uint32_t m_currentFrame{ 0 };
	float m_timeDelta{ 0 };
};

/*!
 * Resets the current frame and time delta to 0.
 */
void Animation::reset() {
	m_currentFrame = 0;
	m_timeDelta = 0.f;
}

/*!
 * Gets the current frame or nullptr if no frame is found.
 * @return
 */
const Frame* Animation::getCurrentFrame() const {
	return (m_frames.size() == 0 || m_currentFrame >= m_frames.size()) ? nullptr : &m_frames.at(m_currentFrame);
}

size_t Animation::size() const {
	return m_frames.size();
}

/*!
 * Update animation based on the fra
 * @param timedeltaMs Time in milliseconds
 */
void Animation::update(float timeDeltaMs) {
	const Frame* frame = getCurrentFrame();
	if (frame != nullptr)
	{
		m_timeDelta += timeDeltaMs;
		if (m_timeDelta >= frame->getDuration())
		{
			m_timeDelta = static_cast<float>((int32_t)m_timeDelta % frame->getDuration());
			m_currentFrame = (m_currentFrame + 1 >= m_frames.size()) ? 0 : m_currentFrame + 1;
		}
	}
}

float Animation::getTimeDelta() const {
	return m_timeDelta;
}

uint32_t Animation::getCurrentFrameNumber() const {
	return m_currentFrame;
}

uint32_t Animation::getCurrentTileId() const {
	return (getCurrentFrame() != nullptr) ? getCurrentFrame()->getTileId() : 0;
}

void Animation::setCurrentFrame(uint32_t currentFrame) {
	m_currentFrame = currentFrame;
}

void Animation::setTimeDelta(float timeDelta) {
	m_timeDelta = timeDelta;
}
