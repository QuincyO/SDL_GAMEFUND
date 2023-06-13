#pragma once
#include <iostream>
#include <string>
#include <map>
#include <SDL_mixer.h>

using namespace std;

class SoundManager
{
public:
	static bool Init();

	static bool LoadMusic(const string& file_name, const string& id);
	static void UnloadMusic(const string& id);
	static void PlayMusic(const string& id, int loop = -1, int fade_in = 0);
	static void StopMusic(int fade_out = 0);
	static void PauseMusic();
	static void ResumeMusic();
	static void SetMusicVolume(const int vol);


	static bool LoadSound(const string& file_name, const string& id);
	static void UnloadSound(const string& id);
	static void PlaySound(const string& id, int loop = 0, int channel = -1);
	static void StopSound(int channel = -1);
	static void SetSoundVolume(const int vol, int channel = -1);

	static void SetAllVolume(const int vol);

	static void Quit();

private:
	static map<string, Mix_Chunk*> s_sfxs;
	static map<string, Mix_Music*> s_music;

	SoundManager();

};

