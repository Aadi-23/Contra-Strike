#pragma once
#include "raylib.h"
#include "Entity.h"
#include <vector>
#include <list>
#include "CONSTANT.h"



struct GameBorder
{
	Vector2 position = { 0,0 };
	Vector2 size = {5, (float)GetScreenHeight()};
};


class Level
{
private:


	float Background_Layer = 0;
	float Foreground_Layer = 0;
	


	std::list<Enemy>enemies;
	std::list<Ground> ground;
	std::list<Projectile>projectile;
	std::list<Mine>mine;
	std::list<Bridge>bridge;
	

	


	// Temporary vectors
	std::vector<Enemy>tempenemies;
	std::vector<Projectile>tempprojectile;
	std::vector<Ground> tempground;
	std::vector<Mine>tempmine;
	std::vector<Bridge>tempbridge;


public:

	// This is gameboarder i made which is like invisible line in left side of screen that stop player from going outside of screen
	GameBorder gameborder;

	// Storage for all entities
	std::vector<Entity*> all_entities{};

	// The player instances
	Player player{PLAYERSPAWNPOS};

	// Camera for the game
	Camera2D player_camera = { 0 };
	float cameraplayer_offset = 0;
	float game_border_offset = -PLAYERSPAWNPOS.x;

	bool game_over = false;

	// Boolean for the text in the naming screen if player wins or lose
	bool player_won = false;

	// Player score counter
	int score = 0;

	// Win point 
	Vector2 VictoryPosition;


    

	void CameraSpawn(const Player& tempplayer);
	void CameraPositionUpdate(const Player& player);

	Vector2 PositionTransformationInGrid(const float x, const float y);

	
	void SpawnEnemy(const Vector2 enemy_pos);
	void SpawnGround(const Vector2 ground_pos);
	void SpawnMine(const Vector2 mine_pos);
	void SpawnProjectile(const Vector2 projectile_pos, const Vector2 projectile_dir);
	void SpawnBridge(const Vector2 bridge_pos);


	void ParallaxEffect(const Texture2D& background, float& backgroundlayer,const Texture2D &foreground, float &foreground_layer);

	void Player_Entities_Collision();

	void refreshEntities();

	void LevelReset();
	void LevelUpdate();
	void LevelRender();

};

