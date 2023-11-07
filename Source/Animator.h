#pragma once
#include "raylib.h"


enum AnimationState
{
	IDLE, WALK, JUMP,
};

struct Animation
{
	Texture2D* texture = {};
	int Frames = 0;
	
};

class AnimationPlayer
{
private:
	Animation* current_animation = {};
	int frame_counter = 0;
	float framerate = 0;

	// I made this bool So I can pass to animation player if i want the animation to loop or not
	bool animation_loop = false;


public:
	AnimationState animation_state = IDLE;

	int current_frame = 0;
	Rectangle animation_rec{};
	void StartAmination(Animation* anim, const bool anim_loop);
	void animation_update();
	void animation_render(const Vector2 & anim_pos);
};
