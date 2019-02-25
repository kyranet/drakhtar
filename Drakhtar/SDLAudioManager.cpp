#include "SDLAudioManager.h"
#include <iostream>

using namespace std;



SDLAudioManager::SDLAudioManager() :
	SDLAudioManager(8) {
}

SDLAudioManager::SDLAudioManager(int channels) :
	initialized_(false), channels_(channels) {
}

SDLAudioManager::~SDLAudioManager() {
	if (!initialized_)
		return;

	// free all sound effect chucks
	for (const auto &pair : chunks_) {
		if (pair.second != nullptr)
			Mix_FreeChunk(pair.second);
	}

	// free all music sound effect
	for (const auto &pair : music_) {
		if (pair.second != nullptr)
			Mix_FreeMusic(pair.second);
	}

	// close SDL_Mixer
	Mix_Quit();
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


bool SDLAudioManager::loadSound(int tag, string fileName) {
	if (!initialized_)
		return false;

	Mix_Chunk* chunk = Mix_LoadWAV(fileName.c_str());
	if (chunk != nullptr) {
		Mix_Chunk* curr = chunks_[tag];
		if (curr != nullptr)
			Mix_FreeChunk(curr);
		chunks_[tag] = chunk;
		return true;
	}
	else {
		cout << "Couldn't load sound file: " << fileName << endl;
		return false;
	}
}

int SDLAudioManager::playChannel(int tag, int loops, int channel) {
	Mix_Chunk* chunk = chunks_[tag];
	if (chunk != nullptr) {
		return Mix_PlayChannel(channel, chunk, loops);
	}
	else {
		return -1;
	}
}

void SDLAudioManager::pauseChannel(int channel) {
	Mix_Pause(channel);
}

void SDLAudioManager::resumeChanne(int channel) {
	Mix_Resume(channel);
}

void SDLAudioManager::haltChannel(int channel) {
	Mix_HaltChannel(channel);
}

int SDLAudioManager::setChannelVolume(int volume, int channel) {
	return Mix_Volume(channel, volume);
}

int SDLAudioManager::channels() {
	return channels_;
}

bool SDLAudioManager::loadMusic(int tag, string fileName) {
	if (!initialized_)
		return false;

	Mix_Music* music = Mix_LoadMUS(fileName.c_str());
	if (music != nullptr) {
		Mix_Music* curr = music_[tag];
		if (curr != nullptr)
			Mix_FreeMusic(curr);
		music_[tag] = music;
		return true;
	}
	else {
		cout << "Couldn't load music file: " << fileName << endl;
		return false;
	}
}

void SDLAudioManager::playMusic(int tag, int loops) {
	Mix_Music* music = music_[tag];
	if (music != nullptr) {
		Mix_PlayMusic(music, loops);
	}
}

int SDLAudioManager::setMusicVolume(int volume) {
	return Mix_VolumeMusic(volume);
}

void SDLAudioManager::haltMusic() {
	Mix_HaltMusic();
}

void SDLAudioManager::pauseMusic() {
	Mix_PauseMusic();
}

void SDLAudioManager::resumeMusic() {
	Mix_ResumeMusic();
}