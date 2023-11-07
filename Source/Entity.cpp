#include"Entity.h"
#include "Level.h"
#include "CONSTANT.h"
#include "myMath.h"
#include "ResourceManager.h"
#include "CollisionDetection.h"


Player::Player(Vector2 player_pos)
{
	position = player_pos;
	size = PLAYERSIZE;
	direction = { 1,0 };
	color = RED;
	velocity = { 0,0 };
	entitytype = EntityType::PLAYER;
	dead = false;

	player_walk_animation.texture = &ResourceManager::textures.player_walk_spritesheet;
	player_walk_animation.Frames =  (int)(player_walk_animation.texture->width/PLAYERSIZE.x);
	player_jump_animation.texture = &ResourceManager::textures.player_jump_spritesheet;
	player_jump_animation.Frames = (int)(player_jump_animation.texture->width / PLAYERSIZE.x);
	

}

void Player::update(Level* level)
{
	
	// JUMP
	if (IsKeyPressed(KEY_SPACE) && onGround)
	{
		velocity.y =  -PLAYERSPEED;
		onGround = false;
		
	}

	
	// MOVEMENT

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
	{	
		direction = { -1,0 };
		
		isMoving = true;

		// This part i made that handles to keep player in the screen while moving left side 
		if (position.x >= level->gameborder.position.x)
		{
			velocity.x = -PLAYERSPEED;
		}
		else
		{
			velocity.x = 0;
		}

		// Animation fliping 
		if (player_animationplayer.animation_rec.width > 0)
		{
			player_animationplayer.animation_rec.width *= -1;
		}

		
	}
	
	
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
	{
		velocity.x = PLAYERSPEED;
		direction = { 1,0 };

		isMoving = true;

		// Animation Flipping
		if (player_animationplayer.animation_rec.width < 0)
		{
			player_animationplayer.animation_rec.width *= -1;
		}
		
	}
	
	// Here this code i made which apply friction for certain velocity
	if (abs(velocity.x) > 2)
	{
		velocity.x *= DRAG_FRICTION;
		

		
	}
	else
	{
		velocity.x = 0;
		isMoving = false;
	}
	
	
	// This takes offset of player from camera When I move left. I use it So the camera does not jump suddenly to player. it is used in camera update function in level.cpp.
	level->cameraplayer_offset = level->player_camera.target.x - position.x;


	// Gravity

	velocity +=  GRAVITY * GetFrameTime();


	// When health 0 the player should die
	if (health <= 0)
	{
		dead = true;
	}



	// Projectile shooting
	if (IsKeyPressed(KEY_X) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		const Vector2 spawn_offset = { size.x*direction.x,size.y/3 };
		level->SpawnProjectile(position + spawn_offset, direction);
	}


	
}

void Player::render()
{
	// Animation state machine for the player
	
	switch (player_animationplayer.animation_state)
	{
	case(IDLE):
	{
		DrawTextureV(ResourceManager::textures.player_texture, position, WHITE);

		if (velocity.x != 0 && onGround)
		{
			player_animationplayer.animation_state = WALK;
			player_animationplayer.StartAmination(&player_walk_animation, walk_animation_loop);
		}

		if (IsKeyPressed(KEY_SPACE))
		{
			player_animationplayer.animation_state = JUMP;
			player_animationplayer.StartAmination(&player_jump_animation, jump_animation_loop);
		}
	}
	break;
	
	case(WALK):
	{
		player_animationplayer.animation_update();
		player_animationplayer.animation_render(position);

		if (IsKeyPressed(KEY_SPACE))
		{
			player_animationplayer.animation_state = JUMP;
			player_animationplayer.StartAmination(&player_jump_animation, jump_animation_loop);
		}

		if (!isMoving)
		{
			player_animationplayer.animation_state = IDLE;
		}
	}
	break;

	case(JUMP):
	{
		player_animationplayer.animation_update();
		player_animationplayer.animation_render(position);

		if (onGround)
		{
			player_animationplayer.animation_state = IDLE;
		}
	}
	break;
	}

	
}


Enemy::Enemy(Vector2 enemy_pos)
{
	position = enemy_pos;
	size = ENEMYSIZE;
	direction = { -1,0 };
	color = WHITE;
	velocity = { ENEMYMOVEMENTSPEED,0 };
	entitytype = EntityType::ENEMY;
	dead = false;

	enemy_walk_animation.texture = &ResourceManager::textures.enemy_walk_spritesheet;
	enemy_walk_animation.Frames = (int)(ResourceManager::textures.enemy_walk_spritesheet.width / ENEMYSIZE.x);

}


bool Enemy::Detect_player(const Level level)
{
	float player_distance = Vector2Distance(position, level.player.position);
	float detection_thresold = 1200.0f;

	if (player_distance < detection_thresold)
	{
		return true;
	}

	return false;
}

void Enemy::update(Level* level)
{
	if (Detect_player(*level))
	{
		position += velocity * direction.x * GetFrameTime();
		isMoving = true;
	}
}

void Enemy::render()
{
	switch (enemy_animationPlayer.animation_state)
	{
	case(IDLE):
	{
		DrawTextureV(ResourceManager::textures.enemy_texture, position, WHITE);

		if (isMoving)
		{
			enemy_animationPlayer.animation_state = WALK;
			enemy_animationPlayer.StartAmination(&enemy_walk_animation, enemy_walk_animeLoop);
			enemy_animationPlayer.animation_rec.width *= direction.x;
		}
	}
	break;

	case(WALK):
	{
		enemy_animationPlayer.animation_update();
		enemy_animationPlayer.animation_render(position);
	}
	break;

	default:
		break;
	}
}

Projectile::Projectile(Vector2 projectile_pos, Vector2 projectile_direction)
{
	position = projectile_pos;
	size = PROJECTILESIZE;
	velocity = { PROJECTILE_SPEED_X,0 };
	direction = projectile_direction;
	color = WHITE;
	dead = false;
	entitytype = EntityType::PROJECTILE;
}


void Projectile::update(Level* level)
{
	if (dead)
	{
		return;
	}

	// Movement of projectile
	position += velocity * direction * GetFrameTime();

	// Collision with enemy
	Vector2 temp_displacement = velocity * GetFrameTime();
	CollisionValues temp_collision;
	for (Entity* e : level->all_entities)
	{
		if (e->dead)
		{
			continue;
		}

		


		if (e->entitytype == EntityType::ENEMY)
		{
			if (Collision::SweptAABBvsAABB(position, size, temp_displacement, e->position, e->size, &temp_collision))
			{
				e->dead = true;
				dead = true;

				
				level->score += BONUS_POINT;
				
			}
			
		}
	}

	

	// This code i made So Bullet dies after going a bit far as I do not want bullet to go and kill enemy that is not in screen.

	if (Vector2Distance(level->player.position, position) > GetScreenWidth())
	{
		dead = true;
	}
}


Ground::Ground(Vector2 ground_pos)
{
	position = ground_pos;
	size = GROUNDSIZE;
	velocity = { 0,0 };
	direction = { 0,0 };
	entitytype = EntityType::GROUND;
	color = WHITE;
	dead = false;
}


void Ground::update(Level* level)
{

}

Mine::Mine(Vector2 mine_pos)
{
	position = mine_pos + (GRIDCELLSIZE - MINE_SIZE);
	size = MINE_SIZE;
	velocity = { 0,0 };
	direction = { 0,0 };
	color = WHITE;
	entitytype = EntityType::MINE;
	dead = false;
}


void Mine::update(Level* level)
{

}


Bridge::Bridge(Vector2 bridge_pos)
{
	position = bridge_pos;
	size = BRIDGE_SIZE;
	velocity = { 0,0 };
	direction = { 0,0 };
	color = WHITE;
	entitytype = EntityType::BRIDGE;
	dead = false;
}

void Bridge::update(Level* level)
{

}