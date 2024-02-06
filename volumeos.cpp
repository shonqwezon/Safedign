#include "VolumeOS.h"

VolumeOS::VolumeOS() {
    CoInitialize(NULL);
}

VolumeOS::~VolumeOS() {
    CoUninitialize();
}

void VolumeOS::setMinVolume(double minVolume) {
    this->minVolume = static_cast<float>(minVolume);
    if(modeNewValue) setNewVolume();
}

void VolumeOS::setNewVolume() {
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    hr = endpointVolume->SetMasterVolumeLevelScalar(minVolume, NULL);
}

void VolumeOS::changeVolume(bool state) {
    modeNewValue = state;
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);
    IMMDevice* defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume* endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    //the door opened
    if (state) {
        hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
        if (minVolume < currentVolume)
            hr = endpointVolume->SetMasterVolumeLevelScalar(minVolume, NULL);
    }
    //the door closed
    else {
        if (currentVolume < 0.0f) {
            hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
        }
        else
            hr = endpointVolume->SetMasterVolumeLevelScalar(currentVolume, NULL);
    }

    endpointVolume->Release();
}
