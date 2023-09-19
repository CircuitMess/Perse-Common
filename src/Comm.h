#ifndef PERSE_COMMON_COMM_H
#define PERSE_COMMON_COMM_H

enum class ComType : uint8_t {
	Battery,
	DriveDir,
	DriveMode,
	DriveSpeed,
	Volume,
	SignalStrength,
	Disconnect,
	Shutdown,
	ShutdownAck,
	Headlights,
	Error,
};

struct ControlPacket {
	ComType type;
	uint8_t data;
};

#endif //PERSE_COMMON_COMM_H
