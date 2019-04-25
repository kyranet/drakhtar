// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "SDLAudioManager.h"

#include <iostream>
#include <string>

SDLAudioManager* SDLAudioManager::instance_ = nullptr;

SDLAudioManager::SDLAudioManager() : SDLAudioManager(8) {}

SDLAudioManager::SDLAudioManager(const int channels)
    : initialized_(false), channels_(channels) {
  muted_ = false;
  default_ = true;
}

SDLAudioManager::~SDLAudioManager() {
  if (!initialized_) return;

  // free all sound effect chucks
  for (const auto& pair : chunks_) {
    if (pair.second != nullptr) Mix_FreeChunk(pair.second);
  }
  chunks_.clear();

  // free all music sound effect
  for (const auto& pair : music_) {
    if (pair.second != nullptr) Mix_FreeMusic(pair.second);
  }
  music_.clear();

  // close SDL_Mixer
  Mix_Quit();
}

SDLAudioManager* SDLAudioManager::getInstance() {
  if (instance_ == nullptr) instance_ = new SDLAudioManager();
  return instance_;
}

void SDLAudioManager::destroy() {
  if (instance_ != nullptr) {
    delete instance_;
    instance_ = nullptr;
  }
}

bool SDLAudioManager::init() {
  if (initialized_) return false;

  Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  channels_ = Mix_AllocateChannels(channels_);

  initialized_ = true;

  return true;
}

bool SDLAudioManager::loadSound(const int tag, std::string fileName) {
  if (!initialized_) return false;

  const auto mixChunk = Mix_LoadWAV(fileName.c_str());
  if (mixChunk != nullptr) {
    const auto chunk = chunks_[tag];
    if (chunk != nullptr) Mix_FreeChunk(chunk);
    chunks_[tag] = mixChunk;
    return true;
  }
  std::cout << "Couldn't load sound file: " << fileName << "\n";
  return false;
}

int SDLAudioManager::playChannel(const int tag, const int loops,
                                 const int channel) {
  const auto chunk = chunks_[tag];
  if (chunk != nullptr) {
    return Mix_PlayChannel(channel, chunk, loops);
  }
  return -1;
}

int SDLAudioManager::playChannelTimed(const int tag, const int loops,
                                      const int channel, const int ticks) {
  const auto chunk = chunks_[tag];
  if (chunk != nullptr) {
    return Mix_PlayChannelTimed(channel, chunk, loops, ticks);
  }

  return -1;
}

void SDLAudioManager::pauseChannel(const int channel) { Mix_Pause(channel); }

void SDLAudioManager::resumeChannel(const int channel) { Mix_Resume(channel); }

void SDLAudioManager::haltChannel(const int channel) {
  Mix_HaltChannel(channel);
}

int SDLAudioManager::setChannelVolume(const int volume, const int channel) {
  channelVolume_ = volume;
  return Mix_Volume(channel, volume);
}

int SDLAudioManager::channels() { return channels_; }

bool SDLAudioManager::loadMusic(const int tag, std::string fileName) {
  if (!initialized_) return false;

  const auto music = Mix_LoadMUS(fileName.c_str());
  if (music != nullptr) {
    const auto current = music_[tag];
    if (current != nullptr) Mix_FreeMusic(current);
    music_[tag] = music;
    return true;
  }

  std::cout << "Couldn't load music file: " << fileName << std::endl;
  return false;
}

void SDLAudioManager::playMusic(const int tag, const int loops) {
  Mix_Music* music = music_[tag];
  if (music != nullptr) {
    Mix_PlayMusic(music, loops);
  } else {
    music_.erase(tag);
  }
}

int SDLAudioManager::setMusicVolume(const int volume) {
  // volume = 2 is quite low already, play with that number
  musicVolume_ = volume;
  return Mix_VolumeMusic(volume);
}

void SDLAudioManager::haltMusic() { Mix_HaltMusic(); }

void SDLAudioManager::pauseMusic() { Mix_PauseMusic(); }

void SDLAudioManager::resumeMusic() { Mix_ResumeMusic(); }

void SDLAudioManager::fadeOutChannel(const int channel, const int ticks) {
  Mix_FadeOutChannel(channel, ticks);
}

void SDLAudioManager::fadeOutMusic(const int ticks) { Mix_FadeOutMusic(ticks); }

bool SDLAudioManager::getMuted() { return muted_; }

void SDLAudioManager::setMute(bool mute) {
  muted_ = mute;
  defaultSound();
}

void SDLAudioManager::defaultSound() {
  if (!getDefault()) {
    const auto volume = muted_ ? 0 : 80;
    const auto instance = getInstance();

    instance->setChannelVolume(volume, 0);
    instance->setChannelVolume(volume, 1);
    instance->setMusicVolume(volume);
  }
}

int SDLAudioManager::getChannelVolume() { return channelVolume_; }

int SDLAudioManager::getMusicVolume() { return musicVolume_; }

void SDLAudioManager::setDefault(bool value_) {
  default_ = value_;
  defaultSound();
}

bool SDLAudioManager::getDefault() { return default_; }

bool SDLAudioManager::getChannelPlaying(int channel) {
  return Mix_Playing(channel);
}

bool SDLAudioManager::getAllChannelPlaying() { return Mix_Playing; }

bool SDLAudioManager::getMusicPlaying() { return Mix_PlayingMusic; }
