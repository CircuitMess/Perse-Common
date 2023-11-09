#ifndef PERSE_ROVER_MARKERINFO_H
#define PERSE_ROVER_MARKERINFO_H

#include <vector>
#include <array>

enum class MarkerAction : int16_t {
	None = 0,
	TurnRightGoAhead = 5,
	RadioToIngenuity = 100,
	TakeSoilSample = 152,
	GoTowards = 204,
	Rotate180 = 305,
	CameraProspectAround = 341,
	HeadlightsSwitch = 409,
	LifeDetected = 576,
	RendezvousPoint = 636,
	Alert = 686,
	CallSampleLander = 750,
	TurnLeftGoAhead = 785
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