// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "SDLAudioManager.h"
#include <iostream>
#include <string>

SDLAudioManager *SDLAudioManager::instance_ = nullptr;

SDLAudioManager::SDLAudioManager() : SDLAudioManager(8) {}

SDLAudioManager::SDLAudioManager(const int channels)
    : initialized_(false), channels_(channels) {}

SDLAudioManager::~SDLAudioManager() {
  if (!initialized_)
    return;

  // free all sound effect chucks
  for (const auto &pair : chunks_) {
    if (pair.second != nullptr)
      Mix_FreeChunk(pair.second);
  }
  chunks_.clear();

  // free all music sound effect
  for (const auto &pair : music_) {
    if (pair.second != nullptr)
      Mix_FreeMusic(pair.second);
  }
  music_.clear();

  // close SDL_Mixer
  Mix_Quit();
}

SDLAudioManager *SDLAudioManager::getInstance() {
  if (instance_ == nullptr)
    instance_ = new SDLAudioManager();
  return instance_;
}

void SDLAudioManager::destroy() {
  if (instance_ != nullptr) {
    delete instance_;
    instance_ = nullptr;
  }
}

bool SDLAudioManager::init() {
  if (initialized_)
    return false;

  Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  channels_ = Mix_AllocateChannels(channels_);

  initialized_ = true;

  return true;
}

bool SDLAudioManager::loadSound(const int tag, std::string fileName) {
  if (!initialized_)
    return false;

  const auto mixChunk = Mix_LoadWAV(fileName.c_str());
  if (mixChunk != nullptr) {
    const auto chunk = chunks_[tag];
    if (chunk != nullptr)
      Mix_FreeChunk(chunk);
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

void SDLAudioManager::pauseChannel(int channel) { Mix_Pause(channel); }

void SDLAudioManager::resumeChannel(int channel) { Mix_Resume(channel); }

void SDLAudioManager::haltChannel(int channel) { Mix_HaltChannel(channel); }

int SDLAudioManager::setChannelVolume(int volume, int channel) {
  return Mix_Volume(channel, volume);
}

int SDLAudioManager::channels() { return channels_; }

bool SDLAudioManager::loadMusic(int tag, std::string fileName) {
  if (!initialized_)
    return false;

  Mix_Music *music = Mix_LoadMUS(fileName.c_str());
  if (music != nullptr) {
    Mix_Music *curr = music_[tag];
    if (curr != nullptr)
      Mix_FreeMusic(curr);
    music_[tag] = music;
    return true;
  } else {
    std::cout << "Couldn't load music file: " << fileName << std::endl;
    return false;
  }
}

void SDLAudioManager::playMusic(int tag, int loops) {
  Mix_Music *music = music_[tag];
  if (music != nullptr) {
    Mix_PlayMusic(music, loops);
  } else {
    music_.erase(tag);
  }
}

int SDLAudioManager::setMusicVolume(int volume) {
  // volume = 2 is quite low already, play with that number
  return Mix_VolumeMusic(volume);
}

void SDLAudioManager::haltMusic() { Mix_HaltMusic(); }

void SDLAudioManager::pauseMusic() { Mix_PauseMusic(); }

void SDLAudioManager::resumeMusic() { Mix_ResumeMusic(); }

void SDLAudioManager::FadeOutChannel(int channel, int ticks) {
  Mix_FadeOutChannel(channel, ticks);
}

void SDLAudioManager::FadeOutMusic(int ticks) { Mix_FadeOutMusic(ticks); }
