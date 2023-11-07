#include "Level.h"
#include "raymath.h"
#include "CollisionDetection.h"
#include "myMath.h"



Vector2 Level::PositionTransformationInGrid(const float x, const float y)
{
	Vector2 transformed_position;

	transformed_position.x = x * GRIDCELLSIZE.x;
	transformed_position.y = y * GRIDCELLSIZE.y;


	return transformed_position;
}

void Level::CameraSpawn(const Player& tempplayer)
{
	const float camera_offset = 50;
	player_camera.zoom = CAMERA_ZOOM;
	player_camera.offset = {tempplayer.position.x - camera_offset, (float)GetRenderHeight() / 2 + camera_offset  };
	player_camera.target = tempplayer.position;
}

void Level::CameraPositionUpdate(const Player& tempplayer)
{   
	const float camera_offset = 30; // Offset so the player does not go under screen in the left side.
	if (player.direction.x > 0 && cameraplayer_offset <= 0)
	{
		player_camera.target.x = tempplayer.position.x;
		gameborder.position.x = player.position.x + game_border_offset + camera_offset ;
	}
	
}



void Level::SpawnEnemy(const Vector2 enemy_pos)
{
	Enemy enemy(enemy_pos);

	tempenemies.push_back(enemy);
}

void Level::SpawnGround(const Vector2 ground_pos)
{
	Ground ground(ground_pos);

	tempground.push_back(ground);
}

void Level::SpawnMine(const Vector2 mine_pos)
{
	Mine mine(mine_pos);

	tempmine.push_back(mine);
}


void Level::SpawnProjectile(const Vector2 projectile_pos, const Vector2 projectile_dir)
{
	Projectile projectile{ projectile_pos, projectile_dir };

	tempprojectile.push_back(projectile);
}

void Level::SpawnBridge(const Vector2 bridge_pos)
{
	Bridge bridge{ bridge_pos };

	tempbridge.push_back(bridge);
}

// This function i made that i run at the end of frames that adds the entities got spawned during real time and also deletes them at the end of frame
void Level::refreshEntities()       
{
	auto last_entity = std::remove_if(all_entities.begin(), all_entities.end(), [](const Entity* e)->bool {return e->dead; });

	all_entities.erase(last_entity, all_entities.end());

	enemies.remove_if([](const Enemy& e)->bool {return e.dead; });
	projectile.remove_if([](const Projectile& e)->bool {return e.dead; });
	ground.remove_if([](const Ground& e)->bool {return e.dead; });
	mine.remove_if([](const Mine& e)->bool {return e.dead; });
	bridge.remove_if([](const Bridge& e)->bool {return e.dead; });

	while (tempenemies.size() != 0)
	{
		enemies.push_back(tempenemies.back());
		all_entities.push_back(&enemies.back());
		tempenemies.pop_back();
	}

	while (tempprojectile.size() != 0)
	{
		projectile.push_back(tempprojectile.back());
		all_entities.push_back(&projectile.back());
		tempprojectile.pop_back();
	}
	while (tempground.size() != 0)
	{
		ground.push_back(tempground.back());
		all_entities.push_back(&ground.back());
		tempground.pop_back();

	}

	while (tempmine.size() != 0)
	{
		mine.push_back(tempmine.back());
		all_entities.push_back(&mine.back());
		tempmine.pop_back();

	}

	while (tempbridge.size() != 0)
	{
		bridge.push_back(tempbridge.back());
		all_entities.push_back(&bridge.back());
		tempbridge.pop_back();

	}
}


void Level::Player_Entities_Collision()
{
	Vector2 player_displacement = player.velocity * GetFrameTime();


	for (int i = 0; i < 5; i++)
	{
		Entity* closest_entity = nullptr;
		CollisionValues closest_collision = { 1,{0,0} };

		for (Entity* e : all_entities)
		{
			
			if (e->dead)
			{
				continue;
			}
			
			CollisionValues temp_collision = { 1,{0,0} };

			if (Collision::SweptAABBvsAABB(player.position, player.size, player_displacement, e->position, e->size, &temp_collision))
			{
				if (temp_collision.collision_t < closest_collision.collision_t)
				{
					closest_collision = temp_collision;
					closest_entity = e;
				}
			}

			

		

		}


		float t_epsilon = 0.001f;
		player.position += player_displacement * (closest_collision.collision_t - t_epsilon);
		player_displacement = player_displacement * (1 - closest_collision.collision_t);
		player_displacement -= closest_collision.contact_normal * Vector2DotProduct(player_displacement, closest_collision.contact_normal);



		if (closest_entity != nullptr)
		{

			
			// Changes the velocity in relation to the entity it collides with.
			player.velocity -= closest_collision.contact_normal * Vector2DotProduct(player.velocity, closest_collision.contact_normal);
			
			// This is when player lands on anything. So everything behaves like ground.
			if (closest_collision.contact_normal.y == -1)
			{
				player.onGround = true;
			}

			// Collision with enemy
			if (closest_entity->entitytype == EntityType::ENEMY || closest_entity->entitytype == EntityType::MINE)
			{
				player.health--;

				closest_entity->dead = true;

			}



			if (closest_entity->entitytype == EntityType::BRIDGE)
			{
				closest_entity->dead = true;
			}
		}
		
		
	}




}


void Level::LevelUpdate()
{

	// The score updates like the position of the score but it won't go negative like position
	if (player.velocity.x > 0)
	{
		score += (int)(player.velocity.x * GetFrameTime());
	}

	player.update(this);

	// Entities update
	for (Entity* e : all_entities)
	{
		e->update(this);
	}

	// Player lose if it falls of the ground or player dies. I added player size to screen height because the camera has offset So The player dies before reaching bottom.
	if (player.position.y >= GetRenderHeight() + player.size.x|| player.dead)
	{
		game_over = true;
	}


	// This is basic check for win check point through collision.
	if (CheckCollisionPointRec(VictoryPosition,{player.position.x, player.position.y, player.size.x, player.size.y}))
	{
		game_over = true;
		player_won = true; 
	}


	Player_Entities_Collision();
	refreshEntities();

	CameraPositionUpdate(player);
}

void Level::LevelReset()        // Resetting the variables in level and clearing up all entities
{
	score = 0;
	cameraplayer_offset = 0;

	player.position = { PLAYERSPAWNPOS };
	player.health = 3;
	player.dead = false;

	player_camera.target = player.position;
	game_over = false;
	player_won = false;

	all_entities.clear();
	enemies.clear();
	ground.clear();
	mine.clear();
	projectile.clear();
}