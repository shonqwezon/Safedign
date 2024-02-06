#ifndef VOLUMEOS_H
#define VOLUMEOS_H
#include <mmdeviceapi.h>
#include <endpointvolume.h>

class VolumeOS
{

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

#endif // VOLUMEOS_H
