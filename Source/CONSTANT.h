#pragma once
#include "raylib.h"

constexpr int GAME_FPS = 60;

// Collision shapes
 constexpr float CIRCLE_SIZE = 60;
 constexpr Vector2 AABB_SIZE = { 60,60 };
 
 // Player
 constexpr float PLAYERSPEED = 350;
 constexpr Vector2 PLAYERSIZE = { 50.0f, 70.0f };
 constexpr Vector2 PLAYERSPAWNPOS = { 150, 350 };
 constexpr float DRAG_FRICTION = 0.85f;

 constexpr float PLAYER_ROTATIONSPEED = 15.0f;

 // Ground
 constexpr Vector2 GRAVITY = { 0,500 };

 constexpr Vector2 GROUNDSIZE = { 50,60 };


 // Enemy
 constexpr Vector2 ENEMYSIZE = { 50,70 };
 constexpr float ENEMYMOVEMENTSPEED = 100.0f;

 // Projectile
 constexpr Vector2 PROJECTILESIZE = { 15,15 };
 constexpr float PROJECTILE_SPEED_X = 600.f;

 // Mine
 constexpr Vector2 MINE_SIZE = { 50,50 };

 //Bridge
 constexpr Vector2 BRIDGE_SIZE = { 50, 30 };


 // Grid
 constexpr Vector2 GRIDCELLSIZE = { 50,70 };

 //Camera

 constexpr float CAMERA_ZOOM = 0.9f;

 //FONT
 constexpr int GAMEFONT_SIZE = 25;


 constexpr int MAX_INPUT_CHAR = 3;


 // PARALLAX SPEED
 constexpr float BACKGROUND_LAYER_SPEED = 0.5f;
 constexpr float FOREGROUND_LAYER_SPEED = 1.5f;


 constexpr int BONUS_POINT = 500;