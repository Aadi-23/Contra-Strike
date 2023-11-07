#pragma once
#include "GameManager.h"
#include <fstream>

struct Textures
{
	Texture2D player_texture;
	Texture2D player_walk_spritesheet;
	Texture2D player_jump_spritesheet;
	Texture2D Foreground_texture;
	Texture2D Background_texture;
	Texture2D ground_texture;
	Texture2D enemy_texture;
	Texture2D enemy_walk_spritesheet;

	Texture2D mine_texture;
	Texture2D win_flag;
	Texture2D projectile_texture;
	Texture2D bridge_texture;
	Texture2D health_texture;
};


struct ResourceManager
{
	static Textures textures;

	static void LoadLevelFromTxt(Level& level);

	static void LoadResources();
	static void UnloadResources();
};
