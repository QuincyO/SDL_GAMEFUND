#include "TextureManager.h"
#include "Game.h"

#include <iostream>

std::map<std::string, SDL_Texture*> TextureManager::s_textures;

SDL_Texture* TextureManager::Load(const char* path, const std::string key)
{
	SDL_Texture* temp = IMG_LoadTexture(Game::GetInstance().GetRenderer(), path);
	if (temp == NULL)
	{
		std::cout << "Could Not Load Texture: Error - " << IMG_GetError() << std::endl;

	}
	else
	{
		s_textures.emplace(key, temp); //Added TO the Map
		std::cout << "Successfully Loaded Texture: " << key << std::endl;
	}
	return temp;
}

void TextureManager::Unload(const std::string key)
{
	if (s_textures.find(key) != s_textures.end())
	{
		SDL_DestroyTexture(s_textures[key]);
		s_textures.erase(key);
	}
	else
	{
		std::cout << "Could not Unload: " << key << std::endl;
	}
}

SDL_Texture* TextureManager::GetTexture(const std::string key)
{
	return s_textures[key];
}

void TextureManager::Quit()
{
	for (auto const& image : s_textures)
	{
		SDL_DestroyTexture(s_textures[image.first]);
	}
	s_textures.clear();
}