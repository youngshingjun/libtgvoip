//
// libtgvoip is free and unencumbered public domain software.
// For more information, see http://unlicense.org or the UNLICENSE file
// you should have received with this source code distribution.
//

#ifndef LIBTGVOIP_AUDIOINPUTAUDIOUNIT_H
#define LIBTGVOIP_AUDIOINPUTAUDIOUNIT_H

#include <AudioUnit/AudioUnit.h>
#import <AudioToolbox/AudioToolbox.h>
#import <CoreAudio/CoreAudio.h>
#include "../../audio/AudioOutput.h"

namespace tgvoip{ namespace audio{
class AudioOutputAudioUnit : public AudioOutput{

public:
	AudioOutputAudioUnit(std::string deviceID);
	virtual ~AudioOutputAudioUnit();
	virtual void Configure(uint32_t sampleRate, uint32_t bitsPerSample, uint32_t channels);
	virtual void Start();
	virtual void Stop();
	virtual bool IsPlaying();
	void HandleBufferCallback(AudioBufferList* ioData);
	static void EnumerateDevices(std::vector<AudioOutputDevice>& devs);
	virtual void SetCurrentDevice(std::string deviceID);
	
private:
	static OSStatus BufferCallback(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);
	static OSStatus DefaultDeviceChangedCallback(AudioObjectID inObjectID, UInt32 inNumberAddresses, const AudioObjectPropertyAddress *inAddresses, void *inClientData);
	unsigned char remainingData[10240];
	size_t remainingDataSize;
	bool isPlaying;
	AudioUnit unit;
	int hardwareSampleRate;
};
}}

#endif //LIBTGVOIP_AUDIOINPUTAUDIOUNIT_H