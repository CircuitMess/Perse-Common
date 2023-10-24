#ifndef PERSE_COMMON_COMM_H
#define PERSE_COMMON_COMM_H

#include <cstdint>

enum class CommType : uint8_t {
	DriveDir,
	Headlights,
	ArmPosition,
	ArmPinch,
	CameraRotation
};

struct ControlPacket {
	CommType type;
	uint8_t data;
};

struct DriveDir {
	uint8_t dir = 0; //0-7
	float speed = 0.0f; //0 - 1.0
};

enum class HeadlightsMode : uint8_t {
	Off,
	On
};

typedef int8_t ArmPos;
typedef int8_t ArmPinch;
typedef uint8_t CameraRotation;

namespace CommData {
	uint8_t encodeDriveDir(DriveDir dir);
	DriveDir decodeDriveDir(uint8_t raw);
}

#endif //PERSE_COMMON_COMM_H
