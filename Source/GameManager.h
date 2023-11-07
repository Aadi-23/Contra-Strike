#pragma once
#include "CollisionDetection.h"
#include "Level.h"
#include "ScoreManager.h"
#include "ResourceManager.h"

enum GAMESTATES
{
	MENUSCREEN,
	COLLISIONSCREEN,
	GAMESCREEN,
	PAUSESCREEN,
	NAMINGSCREEN,
	ENDSCREEN,
};


struct GameManager
{
	std::stack<GAMESTATES>gamestate;

	Collision collision;

	ScoreManager scoremanager;

	Level level;

	bool isGameRunning = true;

	GAMESTATES currentgamestate = {};


	void GameLoop();
	void DoMenuFrame();
	
};