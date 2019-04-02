// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "AudioManager.h"
#include "SDL_mixer.h"
#include <map>
#include <string>

// TODO(Dani/Miguel): Halt all music method.

class SDLAudioManager : public AudioManager {
  // IMPORTANT NOTES:
  // Channel means one sound, meaning for example a footstep
  // Music means a background sound or a song
public:
  static SDLAudioManager *instance_;
  SDLAudioManager();
  explicit SDLAudioManager(int channels);
  virtual ~SDLAudioManager();

  static SDLAudioManager *getInstance();
  static void destroy();

  // Supposed to be called before start using the object
  virtual bool init();

  // Sound effects
  virtual bool loadSound(int tag, std::string fileName);
  virtual int playChannel(int tag, int loops, int channel);
  virtual int playChannelTimed(int tag, int loops, int channel, int ticks);
  virtual void pauseChannel(int channel);
  virtual void resumeChannel(int channel);
  virtual void haltChannel(int channel);
  virtual int setChannelVolume(int volume, int channel);
  virtual int channels();

  // Music
  virtual bool loadMusic(int tag, std::string fileName);
  virtual void playMusic(int tag, int loops);
  virtual int setMusicVolume(int volume);
  virtual void haltMusic();
  virtual void pauseMusic();
  virtual void resumeMusic();

  // Effects
  virtual void FadeOutChannel(int channel, int ticks);
  virtual void FadeOutMusic(int ticks);

private:
  bool initialized_;
  int channels_;
  std::map<int, Mix_Chunk *> chunks_;
  std::map<int, Mix_Music *> music_;
};
