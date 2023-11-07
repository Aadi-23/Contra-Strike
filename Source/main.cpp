#include "raylib.h"
#include "GameManager.h"


int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(GAME_FPS);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------


    SetExitKey(0);

    // Loading resources and inistializing game loop
    ResourceManager::LoadResources();

    GameManager gamemanager;

    gamemanager.gamestate.push(MENUSCREEN);

    
    gamemanager.level.CameraSpawn(gamemanager.level.player);

    gamemanager.scoremanager.FileReader(gamemanager.scoremanager.temp_highscore);

    // Main game loop
    while (gamemanager.isGameRunning)    // Detect window close button or ESC key
    {
       
       gamemanager.GameLoop();
    }


    //Unloading resources
    ResourceManager::UnloadResources();
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}