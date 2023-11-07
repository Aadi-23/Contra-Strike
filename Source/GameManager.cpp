#include "GameManager.h"



void GameManager::GameLoop()
{
	// I put it inside if condition SO if it doesn't give error if the stack is empty
	if (!gamestate.empty())
	{
		currentgamestate = gamestate.top();
	}

	BeginDrawing();
	ClearBackground(SKYBLUE);

	switch (currentgamestate)
	{
	case(MENUSCREEN):
	{
		
		DrawText("CONTRA STRIKE", GetRenderWidth() /4, GetRenderHeight() / 10, GAMEFONT_SIZE * 2, WHITE);
		DoMenuFrame();

		
	}
	break;

	case(COLLISIONSCREEN):
	{
		
		collision.collision_update();
		collision.collision_render();

		if (collision.exit_collisionscreen)
		{
			gamestate.pop();
			collision.exit_collisionscreen = false;
		}
		
	}
	break;

	case(GAMESCREEN):
	{
		
		level.LevelUpdate();
		level.LevelRender();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			gamestate.push(PAUSESCREEN);
		}

		if (level.game_over)
		{
			gamestate.pop();
			scoremanager.Reset_NameBox();
			gamestate.push(NAMINGSCREEN);
		}
	}
	break;

	case(PAUSESCREEN):
	{
		DoMenuFrame();
	}
	break;

	case(NAMINGSCREEN):
	{
		scoremanager.NamingBoxHandler();
		scoremanager.Nameboxrender(level);

		if (IsKeyPressed(KEY_ENTER))
		{
			scoremanager.FileEditor(level);                  // File reading and writing for highscore
			scoremanager.FileReader(scoremanager.highscores);
			
			gamestate.pop();
			gamestate.push(ENDSCREEN);

		}

	}
	break;

	case(ENDSCREEN):
	{
		Rectangle button_rec;
		button_rec.width = 180;
		button_rec.height = 60;
		button_rec.x = (float)(GetRenderWidth() / 20);
		button_rec.y = (float)(GetRenderHeight() / 20);

		const int button_margin_y = 10;

		scoremanager.Highscore_table_render();
		
		if (GUI::gui_button(button_rec, "MAIN MENU", GAMEFONT_SIZE))
		{
			gamestate.pop();
		}

		button_rec.y += button_rec.height + button_margin_y;

		if (GUI::gui_button(button_rec, "CLEAR", GAMEFONT_SIZE))
		{
			scoremanager.ResetBoard();
		}

		
	}
	break;
	}

	EndDrawing();
}


void GameManager::DoMenuFrame()
{
	const Vector2 button_size = { 200,50 };
	const int button_margin_y = 10;
	const int button_count = 4;

	Rectangle button_rect;
	button_rect.x = (GetRenderWidth() - button_size.x) / 2;
	button_rect.y = (GetRenderHeight() - (button_size.y * button_count) - (button_count - 1) * button_margin_y) / 2;
	button_rect.width = button_size.x;
	button_rect.height = button_size.y;


	// Main menu for starting screen
	if (currentgamestate == MENUSCREEN)
	{
		if (GUI::gui_button(button_rect, "PLAY", 30))
		{
			level.LevelReset();
			isGameRunning = true;
			ResourceManager::LoadLevelFromTxt(level);
			gamestate.push(GAMESCREEN);
		}

		button_rect.y += button_size.y + button_margin_y;

		if (GUI::gui_button(button_rect, "COLLISION", 30))
		{

			gamestate.push(COLLISIONSCREEN);

		}

		button_rect.y += button_size.y + button_margin_y;

		if (GUI::gui_button(button_rect, "EXIT", 30))
		{
			isGameRunning = false;
		}
	}

	// Menu for pause screen during game play
	if (currentgamestate == PAUSESCREEN)
	{
		if (GUI::gui_button(button_rect, "CONTINUE", 30))
		{
			gamestate.pop();
		}

		button_rect.y += button_size.y + button_margin_y;

		if (GUI::gui_button(button_rect, "RESTART", 30))
		{
			level.LevelReset();
			isGameRunning = true;
			ResourceManager::LoadLevelFromTxt(level);
			gamestate.pop();
			

		}

		button_rect.y += button_size.y + button_margin_y;

		if (GUI::gui_button(button_rect, "MAIN MENU", 30))
		{
			gamestate.pop();
			gamestate.pop();
		}
	}

	

	

}


