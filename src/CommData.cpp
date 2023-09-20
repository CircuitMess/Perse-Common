#include "CommData.h"

uint8_t CommData::encodeDriveDir(DriveDir dir){
	//highest 4-bit value indicating direction angle, 0-15 equates to 0-360
	//Lowest 4 bits indicate speed in that direction

	auto angle = (uint8_t) (dir.angle * 15.0f / 360.0f);
	auto val = (uint8_t) (dir.value * 15.0f);

	uint8_t code = (angle << 4) | val;

	return code;
}

DriveDir CommData::decodeDriveDir(uint8_t raw){
	DriveDir dir{};

	uint8_t angle = (raw & 0xF0) >> 4;
	uint8_t value = raw & 0x0F;

	dir.angle = angle * 360.0f / 15.0f;
	dir.value = (float) value / 15.0f;

	return dir;
}