#include "jucy_bus.h"

#include <JuceHeader.h>

using namespace juce;

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

class BypassAudioProcessor : public juce::AudioProcessor
{
public:
  BypassAudioProcessor() = default;

  void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override {}

  void releaseResources() override {}

  void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override {}

  AudioProcessorEditor *createEditor() override { return nullptr; }
  bool hasEditor() const override { return false; }
  const String getName() const override { return "Bypass"; }
  bool acceptsMidi() const override { return false; }
  bool producesMidi() const override { return false; }
  double getTailLengthSeconds() const override { return 0.0; }
  int getNumPrograms() override { return 1; }
  void setCurrentProgram(int index) override{};
  int getCurrentProgram() override { return 0; }
  const String getProgramName(int) override { return "None"; }
  void changeProgramName(int, const String &) override {}
  bool isVST2() const noexcept { return (wrapperType == wrapperType_VST); }

  void getStateInformation(MemoryBlock &destData) override {}
  void setStateInformation(const void *data, int sizeInBytes) override {}
};

void test_run()
{
  juce::AudioProcessorPlayer player;
  juce::AudioDeviceManager deviceManager;

  player.setProcessor(new BypassAudioProcessor());
  deviceManager.addAudioCallback(&player);

  juce::AudioDeviceManager::AudioDeviceSetup audioSetup = {};
  // audioSetup.bufferSize = 1024;
  audioSetup.inputDeviceName = juce::String("BlackHole 2ch");
  audioSetup.outputDeviceName = juce::String("UMC202HD 192k");
  deviceManager.initialise(2, 2, nullptr, false, juce::String(), &audioSetup);

  getchar();
}