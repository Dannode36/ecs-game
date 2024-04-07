#pragma once
#include <cstdint>
class Frame
{
public:
	inline Frame() = default;
	inline Frame(int duration, uint32_t tileId);

	[[nodiscard]] inline int getDuration() const;
	[[nodiscard]] inline uint32_t getTileId() const;

private:
	int m_duration{};		//Frame duration in milliseconds
	uint32_t m_tileId{};	//Local tile ID representing this frame
};

/*!
 * @param duration duration in milliseconds
 * @param tileId TileId
 */
Frame::Frame(int duration, uint32_t tileId) : m_duration{ duration }, m_tileId{ tileId }
{
}

int Frame::getDuration() const {
	return m_duration;
}

uint32_t Frame::getTileId() const {
	return m_tileId;
}
