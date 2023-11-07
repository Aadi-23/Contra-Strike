Programming in C/C++ 4: Computer Games in 2D - 5SD814 - 2023

Name : Adarsh Kumar

This game is called "CONTRA STRIKE"
In this project, I had to make a 2D game including some verious features that include animation, highscore table and some basic game engine features.
This game is inspired from a old game called "Contra" which has really nice side scroller platformer.


The game can be run by opening the "raylib_template.sln" and running it.

This game controls are :
Arrow keys or WASD for movement.
Mouse Left button for shooting projectiles.
Space bar for Jumping.



In the project, The game is written in C++ with Object orientation methodology.It includes various file :-

CPP Files :
main.cpp - This is default cpp file that runs the initial code that goes into a loop after intializing the raylib window and loading all resources.
GameManager.cpp - This file has the state machince for the different windows in the game.
GUI.cpp - It is a prototype gui function made that can be untilized anywhere in the project.
Collision.cpp - This is cpp file where the collision prototype function for the game exist.
Level.cpp - Level.cpp is place where the whole game level run. All the methods that need to run a level.
ResourceManager.cpp - Here,I load any type of external resource like text files and texture for the game gets loaded.
Entity.cpp - This file handles all the entities of the game and their methodes.
ScoreManager.cpp - This files has fucntions that renders and update the highscore table as well as it also handles reading and writing scores from a text file.
Animator.cpp - This files handles then animation part. It has animation and animation player.

Header Files : 

Entity.h - The entity header files includes has declaration for the all entities in the game and their functionality.
Level.h - The level header files has the declaration for the methods and variable of the game. it also has the storage where the entities gets stored.
ResourceManager.h - This file has declaration for the textures in the game and methods for loading resource.
Collision.h - It has the object declaration that also includes the variables and methods for the certain object.
GUI.h - This includes an struct for GUI object that has methods for creating buttons in the game.
GameManger.h - This file has oject which contains declaration of different instances of level, scoremanager and other objects. It has methods which runs the game loop.
ScoreManager.h - This head file is for the variables and methods that handles the score management for the game.
Animator.h - Here i have decaleration for the variable and struct that needed for the animation. It also has statemachine which can be made anywhere need.
