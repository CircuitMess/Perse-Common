#ifndef PERSE_ROVER_DRIVEINFO_H
#define PERSE_ROVER_DRIVEINFO_H

#include "DriveMode.h"
#include "RingBuffer.h"
#include <vector>
#include <memory>

struct CamFrame {
	size_t size = 0;
	void* data = nullptr;
};

struct MotorInfo {
	int8_t frontLeft;
	int8_t frontRight;
	int8_t backLeft;
	int8_t backRight;
};

struct DriveInfo {
	DriveMode mode = DriveMode::Idle;
	MotorInfo motors = { };
	CamFrame frame = { };

	virtual ~DriveInfo();

	static constexpr size_t baseSize = sizeof(DriveMode) + sizeof(MotorInfo) + sizeof(CamFrame::size);

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
