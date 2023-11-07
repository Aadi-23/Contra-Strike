#include "Level.h"
#include "ResourceManager.h"




void Level::ParallaxEffect(const Texture2D& background, float &background_layer,const Texture2D& foreground, float& foreground_layer)
{
	const float background_width = (float)background.width;
	const float foreground_width = (float)foreground.width;

	// Scale for the texture
	const float texture_scale = 0.7f;

	if (player.velocity.x > 0)
	{
		background_layer -= BACKGROUND_LAYER_SPEED;
		foreground_layer -= FOREGROUND_LAYER_SPEED;
	}
	



	if (background_layer <= -background_width * texture_scale )
	{
		background_layer = 0;
	}

	if (foreground_layer <= -foreground_width * texture_scale)
	{
		foreground_layer = 0;
	}



	// Background Layer
	DrawTextureEx(background, { background_layer, 0 }, 0, texture_scale, WHITE);
	DrawTextureEx(background, { background_width * texture_scale + background_layer, 0 }, 0, texture_scale, WHITE);

	//Foreground Layer
	DrawTextureEx(foreground, { foreground_layer, 0 }, 0, texture_scale, WHITE);
	DrawTextureEx(foreground, { foreground_width * texture_scale + foreground_layer, 0 }, 0, texture_scale, WHITE);

}



void Level::LevelRender()
{

	// Parallax

	ParallaxEffect(ResourceManager::textures.Background_texture, Background_Layer, ResourceManager::textures.Foreground_texture, Foreground_Layer);


	// Score rendering
	int Text_size = MeasureText("Score",GAMEFONT_SIZE);
	
	DrawText(TextFormat("Score: %i", score), GetRenderWidth() / 2 - Text_size , 0, GAMEFONT_SIZE, BLACK);



	// Player Health
	for (int i = 0; i < player.health; i++)
	{
		const Vector2 temp_size = {30,30};
		const Vector2 temp_healthPos = {(float)(GetRenderWidth()/20) + i*(temp_size.x +10) , (float)GetRenderHeight()/20};
		DrawTextureV(ResourceManager::textures.health_texture, temp_healthPos, RED);
	}



	// All entities that need to be inside camera
	BeginMode2D(player_camera);

	player.render();

	// This is win point flag for player 
	DrawTextureV(ResourceManager::textures.win_flag, VictoryPosition, WHITE);


	// Here I made this external loop for enemies as render is not inherited function
	for (Enemy& enemy : enemies)
	{
		enemy.render();
	}


	for (Entity* entity : all_entities)
	{
		switch (entity->entitytype)
		{
		break;

		case(EntityType::GROUND):
		{
			DrawTextureV(ResourceManager::textures.ground_texture, entity->position, entity->color);
		}
		break;

		case(EntityType::PROJECTILE):
		{
			DrawTextureV(ResourceManager::textures.projectile_texture, entity->position,entity->color);
		}
		break;

		case(EntityType::MINE):
		{
			
			DrawTextureV(ResourceManager::textures.mine_texture, entity->position, entity->color);
		}
		break;

		case(EntityType::BRIDGE):
		{
			DrawTextureV(ResourceManager::textures.bridge_texture, entity->position,entity->color);
		}
		break;
		}
	}


	EndMode2D();
}

