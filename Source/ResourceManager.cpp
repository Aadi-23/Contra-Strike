#pragma once
#include"ResourceManager.h"
#include <string>
#include "raylib.h"


Textures ResourceManager::textures;

constexpr const char* LevelTextFile = "./Assets/level.txt";

void ResourceManager::LoadLevelFromTxt(Level& level)
{
	std::string leveltext = LoadFileText(LevelTextFile);

	int index = 0;
	float x_pos = 0;
	float y_pos = 0;

	for (char& c : leveltext)
	{
		switch (c)
		{
		case('-'): // skip if there is hyphen
		{
			x_pos++;
		}
		break;

		case('e'):
		{
			level.SpawnEnemy(level.PositionTransformationInGrid(x_pos,y_pos));                     // I call entity spaner and i use the function So i can transform the index of text file into coordinated in the game.
			x_pos++;
		}
		break;

		case('g'):
		{
			level.SpawnGround(level.PositionTransformationInGrid(x_pos, y_pos));
			x_pos++;
		}
		break;

		case('m'):
		{
			level.SpawnMine(level.PositionTransformationInGrid(x_pos, y_pos));

			x_pos++;
		}
		break;

		case('b'):
		{
			level.SpawnBridge(level.PositionTransformationInGrid(x_pos, y_pos));

			x_pos++;
		}
		break;
		case('w'):
		{
			level.VictoryPosition = level.PositionTransformationInGrid(x_pos, y_pos);
			x_pos++;
		}
		break;

		case('\n'):  // change line
		{
			y_pos++;
			x_pos = 0;
		}
		break;

		default:          // Skip anyway
		{
			x_pos++;
		}
			break;
		}
	}
}

void ResourceManager::LoadResources()
{
	textures.player_texture = LoadTexture("./Assets/Texture/player.png");
	textures.player_walk_spritesheet = LoadTexture("./Assets/Texture/player_walk_sheet.png");
	textures.player_jump_spritesheet = LoadTexture("./Assets/Texture/player_jump_sheet.png");
	textures.Foreground_texture = LoadTexture("./Assets/Texture/foreground.png");
	textures.Background_texture = LoadTexture("./Assets/Texture/background.png");
	textures.ground_texture = LoadTexture("./Assets/Texture/ground.png");
	textures.enemy_texture = LoadTexture("./Assets/Texture/enemy.png");
	textures.enemy_walk_spritesheet = LoadTexture("./Assets/Texture/enemy_walk_sheet.png");
	textures.mine_texture = LoadTexture("./Assets/Texture/mine.png");
	textures.win_flag = LoadTexture("./Assets/Texture/win_point.png");
	textures.projectile_texture = LoadTexture("./Assets/Texture/projectile.png");
	textures.bridge_texture = LoadTexture("./Assets/Texture/bridge.png");
	textures.health_texture = LoadTexture("./Assets/Texture/health.png");

}

void ResourceManager::UnloadResources()
{
	UnloadTexture(textures.player_texture);
	UnloadTexture(textures.Foreground_texture);
	UnloadTexture(textures.Background_texture);
	UnloadTexture(textures.player_walk_spritesheet);
	UnloadTexture(textures.player_jump_spritesheet);
	UnloadTexture(textures.ground_texture);
	UnloadTexture(textures.enemy_texture);
	UnloadTexture(textures.enemy_walk_spritesheet);
	UnloadTexture(textures.mine_texture);
	UnloadTexture(textures.projectile_texture);
	UnloadTexture(textures.win_flag);
	UnloadTexture(textures.bridge_texture);
	UnloadTexture(textures.health_texture);
}