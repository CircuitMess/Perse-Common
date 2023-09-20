#ifndef PERSE_COMMON_COMM_H
#define PERSE_COMMON_COMM_H

enum class CommType : uint8_t {
	DriveDir
};

struct ControlPacket {
	CommType type;
	uint8_t data;
};

#endif //PERSE_COMMON_COMM_H
