#pragma once
#include "raylib.h"
#include "Animator.h"


enum class EntityType
{
	NONE,
	PLAYER,
	ENEMY,
	GROUND,
	PROJECTILE,
	MINE,
	BRIDGE,
};



class Level;


class Entity
{
public:
	Vector2 position = { 0,0 };
	Vector2 size = { 0,0 };
	Vector2 velocity = { 0,0 };
	Vector2 direction = {0,0};
	EntityType entitytype = EntityType::NONE;
	Color color = WHITE;
	bool dead = false;


	virtual void update(Level* level) = 0;


	virtual ~Entity() = default;

};



class Player : public Entity
{
private:
	

	bool isMoving = false;

	bool walk_animation_loop = true;
	bool jump_animation_loop = false;

	Animation player_walk_animation = {};
	Animation player_jump_animation = {};
	AnimationPlayer player_animationplayer = {};



public:

	int health = 3;

	bool onGround = true;

	Player(Vector2 player_pos);


	void update(Level* level) override;
	void render();

};


class Enemy : public Entity
{
private:
	bool isMoving = false;
	bool enemy_walk_animeLoop = true;
public:
	Enemy() {};
	Enemy(Vector2 enemy_pos);

	Animation enemy_walk_animation{};
	AnimationPlayer enemy_animationPlayer{};

	bool Detect_player(const Level level);
	void update(Level* level) override;
	void render();
};


class Projectile : public Entity
{
public:
	Projectile() {};
	Projectile(Vector2 projectile_pos, Vector2 projectile_direction);

	void update(Level* level) override;
};

class Mine : public Entity
{
public:
	Mine() {};
	Mine(Vector2 Mine_pos);
	
	void update(Level* level) override;
};


class Ground : public Entity
{
public:
	Ground(Vector2 gorund_pos);
	
	void update(Level* level) override;
};

class Bridge : public Entity
{
public:
	Bridge(Vector2 bridge_pos);

	void update(Level* level) override;
};


