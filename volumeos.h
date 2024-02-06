#ifndef VOLUME_OS_H
#define VOLUME_OS_H

#define DLL_EXPORTS

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#include <mmdeviceapi.h>
#include <endpointvolume.h>

class DLL_API VolumeOS {
public:
	VolumeOS();
	~VolumeOS();
	void changeVolume(bool state);
	void setNewVolume();
	void setMinVolume(double minVolume);

private:
	HRESULT hr{ 0 };
	float minVolume{ 0.1f };
	float currentVolume{ -1.0f };
	bool modeNewValue{ false };
};

#endif