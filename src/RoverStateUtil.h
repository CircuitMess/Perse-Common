#ifndef PERSE_ROVER_ROVERSTATE_H
#define PERSE_ROVER_ROVERSTATE_H

#include <stdint.h>

uint8_t encodeRoverState(uint8_t value, bool local);

bool decodeRoverState(uint8_t inValue, uint8_t& outValue);

#endif //PERSE_ROVER_ROVERSTATE_H
