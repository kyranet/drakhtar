// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <map>
#include <string>

#include "AudioManager.h"
#include "SDL_mixer.h"

// TODO(Dani/Miguel): Halt all music method.

class SDLAudioManager final : public AudioManager {
  // IMPORTANT NOTES:
  // Channel means one sound, meaning for example a footstep
  // Music means a background sound or a song
  static SDLAudioManager* instance_;

 public:
  SDLAudioManager();
  explicit SDLAudioManager(int channels);
  ~SDLAudioManager();

  static SDLAudioManager* getInstance();
  static void destroy();

  // Supposed to be called before start using the object
  bool init() override;

  // Sound effects
  bool loadSound(int tag, std::string fileName) override;
  int playChannel(int tag, int loops, int channel) override;
  int playChannelTimed(int tag, int loops, int channel, int ticks) override;
  void pauseChannel(int channel) override;
  void resumeChannel(int channel) override;
  void haltChannel(int channel) override;
  int setChannelVolume(int volume, int channel) override;
  int channels() override;

  // Music
  bool loadMusic(int tag, std::string fileName) override;
  void playMusic(int tag, int loops) override;
  int setMusicVolume(int volume) override;
  void haltMusic() override;
  void pauseMusic() override;
  void resumeMusic() override;

  // Effects
  void fadeOutChannel(int channel, int ticks);
  void fadeOutMusic(int ticks);

  // check sound propertiees: default system and muted
  bool getMuted();
  void setMute(bool mute);
  void defaultSound();
  int getChannelVolume();
  int getMusicVolume();
  void setDefault(bool value_);
  bool getDefault();
  bool getChannelPlaying(int channel);
  bool getAllChannelPlaying();
  bool getMusicPlaying();

 private:
  bool initialized_;
  bool default_;
  bool muted_;
  int channels_;
  int musicVolume_ = 80, channelVolume_ = 80;
  std::map<int, Mix_Chunk*> chunks_;
  std::map<int, Mix_Music*> music_;
};
