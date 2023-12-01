#include "RoverStateUtil.h"

uint8_t encodeRoverState(uint8_t value, bool local){
	uint8_t result = value & 0x7F;

	if(local){
		result |= 0x80;
	}

	return result;
}

bool decodeRoverState(uint8_t inValue, uint8_t& outValue){
	outValue = inValue & 0x7F;

	return (inValue & 0x80) != 0;
}