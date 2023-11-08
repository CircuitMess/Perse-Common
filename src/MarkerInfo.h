#ifndef PERSE_ROVER_MARKERINFO_H
#define PERSE_ROVER_MARKERINFO_H

#include <vector>
#include <array>

enum class MarkerAction : uint8_t {
	None,
	Forward,
	Rotate180
};

struct Marker {
	std::array<std::pair<int16_t, int16_t>, 4> projected;
	uint16_t id = 0;
};

struct MarkerInfo {
	MarkerAction action;
	std::vector<Marker> markers;
};

#endif //PERSE_ROVER_MARKERINFO_H