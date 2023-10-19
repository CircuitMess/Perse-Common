#include "CommData.h"
#include <algorithm>
#include <cmath>

uint8_t CommData::encodeDriveDir(DriveDir dir){
	//highest 4-bit value indicating direction
	//Lowest 4 bits indicate speed in that direction
	dir.dir = std::clamp(dir.dir, (uint8_t)0, (uint8_t)7);
	dir.speed = std::clamp(dir.speed, 0.0f, 1.0f);

	const auto speed = (uint8_t) std::round(dir.speed * 31.0f);

	return (speed << 3 | dir.dir);
}

DriveDir CommData::decodeDriveDir(uint8_t raw){
	uint8_t speed = raw >> 3;
	uint8_t dir = raw & 0b111;

	return { dir, (float) speed };
}

uint8_t CommData::encodeModulePlug(ModulePlugData plugData){
	uint8_t data = (plugData.insert << 7) | ((uint8_t) plugData.bus << 6) | (uint8_t) plugData.type;

	return data;
}

ModulePlugData CommData::decodeModulePlug(uint8_t raw){
	ModulePlugData data{};
	data.insert = raw >> 7;
	data.bus = (ModuleBus) ((raw >> 6) & 0b1);
	data.type = (ModuleType) (raw & 0b111111);

	return data;
}