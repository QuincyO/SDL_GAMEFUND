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

SDL_Texture* TextureManager::LoadString(const char* TEXT,std::string key)
{

	s_textures[key] = nullptr;

	TTF_Font* tempFont = TTF_OpenFont("assets/fonts/kenpixel.ttf", 5);

	SDL_Surface* surface = TTF_RenderText_Solid(tempFont, TEXT, { 255,255,255,255 });

	if (surface == NULL)
	{
		std::cout << "Surface Failed to load" << std::endl;
	}
	s_textures[key] = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

	SDL_FreeSurface(surface);


	return s_textures[key];
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