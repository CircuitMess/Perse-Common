#ifndef PERSE_COMMON_COMM_H
#define PERSE_COMMON_COMM_H

#include <cstdint>

enum class CommType : uint8_t {
	DriveDir
};

struct ControlPacket {
	CommType type;
	uint8_t data;
};

struct DriveDir {
	uint16_t angle; //0-360
	float value; //0 - 1.0
};

namespace CommData {

uint8_t encodeDriveDir(DriveDir dir);
DriveDir decodeDriveDir(uint8_t raw);

}

#endif //PERSE_COMMON_COMM_H
