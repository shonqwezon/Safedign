#ifndef VOLUME_OS_H
#define VOLUME_OS_H

#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>

class VolumeOS {
public:
	VolumeOS();
	~VolumeOS();
	void changeVolume(bool state);
	void setMinVolume(double minVolume);

private:
	HRESULT hr{ 0 };
	float minVolume{ 0.0f };
	float currentVolume{ -1.0f };
};
#endif