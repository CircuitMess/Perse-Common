#ifndef PERSE_ROVER_DRIVEINFO_H
#define PERSE_ROVER_DRIVEINFO_H

#include "RingBuffer.h"
#include "MarkerInfo.h"
#include <vector>
#include <memory>

struct CamFrame {
	size_t size = 0;
	void* data = nullptr;
};

struct MotorInfo {
	int8_t left;
	int8_t right;
};

struct DriveInfo {
	CamFrame frame = {};
	MarkerInfo markerInfo = {};

	virtual ~DriveInfo();

	static constexpr size_t baseSize = sizeof(CamFrame::size) + sizeof(MarkerInfo::action) + sizeof(size_t);

	/**
	 * Returns size of struct in binary form, including all elements and sub-elements.
	 * Note: data size varies by DriveMode.
	 * @return Struct size.
	 */
	virtual size_t size() const;

	/**
	 * Serializes data to destination buffer. Buffer must be at least DriveInfo::size() bytes long.
	 * @param dest Destination buffer
	 */
	void toData(void* dest) const;

	/**
	 * Deserializes data from a RingBuffer to a DriveInfo struct.
	 * Buffer is expected to have the binary data on the first byte, and contains 'size' bytes of binary DriveInfo data.
	 * @param buf RingBuffer containing the binary data, starting from the first byte.
	 * @param size Size of DriveInfo binary data (bytes from header to trailer in a UDP packet)
	 * @return unique_ptr to a DriveInfo struct
	 */
	static std::unique_ptr<DriveInfo> deserialize(RingBuffer& buf, size_t size);
};

#define FEED_ENV_LEN 8
const extern uint8_t FrameHeader[FEED_ENV_LEN];
const extern uint8_t FrameTrailer[FEED_ENV_LEN];
const extern uint8_t FrameSizeShift[4];

#endif //PERSE_ROVER_DRIVEINFO_H
