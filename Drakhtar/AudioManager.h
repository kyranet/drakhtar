#pragma once
#include <string>
using namespace std;
class AudioManager
{
public:
	AudioManager();
	virtual ~AudioManager();

	// supposed to be called before start using the object
	virtual bool init() = 0;

	// sound effects
	virtual bool loadSound(int tag, string fileName) = 0;
	virtual int playChannel(int tag, int loops, int channel = -1) = 0;
	virtual int playChannelTimed(int tag, int loops, int channel, int ticks) = 0;
	virtual void pauseChannel(int channel = -1) = 0;
	virtual void resumeChanne(int channel = -1) = 0;
	virtual void haltChannel(int channel = -1) = 0;
	virtual int setChannelVolume(int volume, int channel = -1) = 0;
	virtual int channels() = 0;

	// music
	virtual bool loadMusic(int tag, string fileName) = 0;
	virtual void playMusic(int tag, int loops = -1) = 0;
	virtual int setMusicVolume(int volume) = 0;
	virtual void haltMusic() = 0;
	virtual void pauseMusic() = 0;
	virtual void resumeMusic() = 0;

};

