#include "SoundManager.h"
#include <iostream>

map<string, Mix_Chunk*> SoundManager::s_sfxs;
map<string, Mix_Music*> SoundManager::s_music;

bool SoundManager::Init()
{
	int errorCode = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	if (errorCode == 0)
	{
		cout << "Mix_OpenAudio() Succeeded!" << endl;

	}
	else
	{
		cout << "Mix_OpenAudio Faield. Error: " << Mix_GetError() << endl;
		system("pause");
		return false;
	}
	int audioFlags = MIX_INIT_MP3;
	errorCode = Mix_Init(audioFlags);
	if (errorCode != audioFlags)
	{
		cout << "Mix_OpenAudio() Faiiled. Error: " << Mix_GetError() << endl;
		system("pause");
		return false;
	}
	return true;
}

bool SoundManager::LoadMusic(const string& file_name, const string& id)
{
	Mix_Music* pMusic = Mix_LoadMUS(file_name.c_str());
	if (pMusic == nullptr)
	{
		cout << "Could not load Music: Error - " << Mix_GetError() << endl;
		return false;
	}
	s_music[id] = pMusic;
	return true;
}

void SoundManager::UnloadMusic(const string& id)
{
	if (s_music.find(id) != s_music.end())
	{
		Mix_FreeMusic(s_music[id]);
		s_music.erase(id);
	}
	else
	{
		cout << "Could not unload '" << id << "' - id not found" << endl;
	}
}

void SoundManager::PlayMusic(const string& id, const int loop /* = -1*/, const int fade_in /*= 0*/)
{
	if (Mix_FadeInMusic(s_music[id], loop, fade_in) == -1)
	{
		cout << "Unable to play Music: Error - " << Mix_GetError() << endl;
	}
}

void SoundManager::StopMusic(const int fade_out/* = 0*/)
{
	if (Mix_PlayingMusic())
	{
		Mix_FadeOutMusic(fade_out);
	}
}

void SoundManager::PauseMusic()
{
	if (Mix_PlayingMusic())
	{
		Mix_PauseMusic();
	}
}

void SoundManager::ResumeMusic()
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void SoundManager::SetMusicVolume(const int vol)
{
	if (vol >= 0 && vol <= 128)
	{
		Mix_VolumeMusic(vol);
	}
}

bool SoundManager::LoadSound(const string& file_name, const string& id)
{
	Mix_Chunk* pChunk = Mix_LoadWAV(file_name.c_str());
	if (pChunk == nullptr)
	{
		cout << "Could not load SFX: Error - " << Mix_GetError() << std::endl;
		return false;
	}
	s_sfxs[id] = pChunk;
	return true;
}

void SoundManager::UnloadSound(const string& id)
{
	if (s_sfxs.find(id) != s_sfxs.end())
	{
		Mix_FreeChunk(s_sfxs[id]);
		s_sfxs.erase(id);
	}
	else
	{
		cout << "Could not Unload '" << id << "' - id not found!" << endl;
	}
}

void SoundManager::PlaySound(const string& id, const int loop /* = 0*/, const int channel /*=-1*/)
{
	if (channel != -1 && Mix_Playing(channel))
		return;
	if (Mix_PlayChannel(channel, s_sfxs[id], loop) == -1)
		cout << "unable to play SFX: Error - " << Mix_GetError() << endl;
}

void SoundManager::StopSound(int channel)
{
	Mix_HaltChannel(channel);
}

void  SoundManager::SetSoundVolume(const int vol, const int channel /* =-1*/)
{
	if (vol >= 0 && vol <= 128)
	{
		Mix_Volume(channel, vol);
	}
}

void SoundManager::SetAllVolume(const int vol)
{
	SetMusicVolume(vol);
	SetSoundVolume(vol);
}

void SoundManager::Quit()
{
	//Clean up sound effects.
	if (Mix_Playing(-1))
		Mix_HaltChannel(-1); //Halt All Channels.

	for (auto const& i : s_sfxs)
	{
		Mix_FreeChunk(s_sfxs[i.first]);
	}
	s_sfxs.clear();

	//Clean Up Music
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}
	for (auto const& i : s_music)
	{
		Mix_FreeMusic(s_music[i.first]);
	}
	s_music.clear();

	//Quit
	Mix_CloseAudio();
	Mix_Quit();
}