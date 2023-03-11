#include "jucy_bus.h"

#include <JuceHeader.h>

void enumerate_audio_devices() 
{
  juce::AudioDeviceManager deviceManager;

  {
    printf("-------------------------\n");
    printf("---- Audio Devices ------\n");

    for (auto &deviceType : deviceManager.getAvailableDeviceTypes())
    {
      printf("%s\n", deviceType->getTypeName().toRawUTF8());

      printf(" Inputs:\n");
      for (auto &name : deviceType->getDeviceNames(true))
        printf("  - %s\n", name.toRawUTF8());

      printf(" Outputs:\n");
      for (auto &name : deviceType->getDeviceNames(false))
        printf("  - %s\n", name.toRawUTF8());
    }

    printf("-------------------------\n");
  }
}