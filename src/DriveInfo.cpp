#include "DriveInfo.h"
#include <cstring>
#include <esp_log.h>

const uint8_t FrameHeader[FEED_ENV_LEN] = { 0x18, 0x20, 0x55, 0xf2, 0x5a, 0xc0, 0x4d, 0xaa };
const uint8_t FrameTrailer[FEED_ENV_LEN] = { 0x42, 0x2c, 0xd9, 0xe3, 0xff, 0xa0, 0x11, 0x01 };
const uint8_t FrameSizeShift[4] = { 2, 3, 1, 0 };

static const char* tag = "DataModel";

DriveInfo::~DriveInfo(){
	if(frame.data){
		free(frame.data);
		frame.data = nullptr;
	}
}

size_t DriveInfo::size() const{
	size_t size = baseSize + frame.size;
	return size;
}

void DriveInfo::toData(void* dest) const{
	auto data = (uint8_t*) dest;
	memcpy(data, &mode, sizeof(DriveMode));
	data += sizeof(DriveMode);

	memcpy(data, &motors, sizeof(MotorInfo));
	data += sizeof(MotorInfo);

	memcpy(data, &frame.size, sizeof(CamFrame::size));
	data += sizeof(CamFrame::size);

	memcpy(data, frame.data, frame.size);
	data += frame.size;
}

std::unique_ptr<DriveInfo> DriveInfo::deserialize(RingBuffer& buf, size_t size){
	if(size < baseSize){
		ESP_LOGE(tag, "Couldn't create DriveInfo from data, required size: %d, received: %d\n", baseSize, size);
		return nullptr;
	}
	DriveMode mode;

	buf.read((uint8_t*) (&mode), sizeof(DriveMode));

	std::unique_ptr<DriveInfo> info = std::make_unique<DriveInfo>();
	info->mode = mode;

	buf.read((uint8_t*) &info->motors, sizeof(MotorInfo));
	buf.read((uint8_t*) &info->frame.size, sizeof(CamFrame::size));

	if(buf.readAvailable() < info->frame.size){
		ESP_LOGE(tag, "Deserialize data too short, lacks JPG frame");
		return nullptr;
	}

	info->frame.data = malloc(info->frame.size);

	if(info->frame.data == nullptr){
		ESP_LOGE(tag, "Couldn't allocate buffer for jpg frame data");
		return nullptr;
	}

	buf.read((uint8_t*) info->frame.data, info->frame.size);

	return info;
}
