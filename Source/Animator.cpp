#include "Animator.h"
#include "CONSTANT.h"

void AnimationPlayer::StartAmination(Animation* anim, bool anim_loop)
{
	current_animation = anim;
	framerate = (float)( GAME_FPS / (anim->Frames*2));
	animation_rec = { 0,0, (float)(anim->texture->width / anim->Frames), (float)anim->texture->height };
	animation_loop = anim_loop;
	current_frame = 0;

}

void AnimationPlayer::animation_update()
{
	frame_counter++;
	
	if (frame_counter >= framerate)
	{
		
		// I made this if condition So If the current frame is still no at the end or animation loop in true. It will update current frame. This way i controll the animation loop.
		if (current_frame < current_animation->Frames - 1 || animation_loop)
		{
			current_frame++;
			frame_counter = 0;
		}

		
		// Resetting the current frame in sprite sheet
		if (current_frame > current_animation->Frames - 1 && animation_loop)
		{
 			current_frame = 0;
		}

		// Updating the source rectange position in sprite sheet
		animation_rec.x = (float)(current_frame * (current_animation->texture->width / current_animation->Frames));
	}
	
	

	

}

void AnimationPlayer::animation_render(const Vector2& anim_pos)
{
	DrawTextureRec(*current_animation->texture, animation_rec, anim_pos, WHITE);
}