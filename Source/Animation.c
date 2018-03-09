#include "stdafx.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct
{
  float mX;
  float mY;
}TextureOffset;

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct Animation
{
	// Pointer to the sprite associated with the animation.
	SpritePtr sprite;

	// The current frame being displayed.
	unsigned int frameIndex;

	// The maximum number of frames in the sequence.
	unsigned int frameCount;

	// The time remaining for the current frame.
	float frameDelay;

	// The amount of time to display each frame.
	// (Used only when playing simple animations (0 .. numFrame).)
	float frameDuration;

	// True if the animation is running; false if the animation has stopped.
	bool isRunning;

	// True if the animation loops back to the beginning.
	bool isLooping;

	// True if the end of the animation has been reached, false otherwise.
	// (Hint: This should be true for only one game loop.)
	bool isDone;

	// The animation sequence currently being played, if any.
	AnimationSequencePtr	sequence;

} Animation;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void AnimationAdvanceFrame(AnimationPtr animation);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

AnimationPtr AnimationCreate(SpritePtr sprite)
{
	AnimationPtr Animate = calloc(1, sizeof(Animation));
	if (Animate)
	{
		Animate->sprite = sprite;
		return Animate;
	}
	return NULL;
}

// Dynamically allocate a clone of an existing animation.
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
AnimationPtr AnimationClone(const AnimationPtr other, SpritePtr sprite)
{
  if (other && sprite)
  {
    AnimationPtr animation = calloc(1, sizeof(Animation));
    if (animation)
    {
      *animation = *other;
      animation->sprite = sprite;
      return animation;
    }
  }
  return NULL;
}

void AnimationFree(AnimationPtr * animation)
{
	if (animation && *animation)
	{
		free(*animation);
		(*animation) = NULL;
	}
}

void AnimationPlay(AnimationPtr animation, int frameCount, float frameDuration, bool isLooping)
{
	if (animation)
	{
		animation->frameCount = frameCount;
		animation->frameDuration = frameDuration;
		animation->isLooping = isLooping;
		animation->isRunning = 1;
	}
}

// Play a complex animation sequence (any frame/any delay).
// Params:
//	 animation = Pointer to the animation object.
//	 sequence = Pointer to the animation sequence to be played.
void AnimationPlaySequence(AnimationPtr animation, AnimationSequencePtr sequence)
{
	if (animation && sequence)
	{
		animation->sequence = sequence;
		animation->frameCount = AnimationSequenceGetFrameCount(sequence);
		animation->frameIndex = 0;

		const AnimationFrame * AFrame = AnimationSequenceGetFrame(sequence, animation->frameIndex);

		SpriteSetFrame(animation->sprite, AFrame->frameIndex);
		
		animation->frameDelay = AFrame->frameDuration;

		animation->isLooping = AnimationSequenceIsLooping(sequence);

		animation->isRunning = 1;

		animation->isDone = 0;
	}
}

// Update the animation.
// Params:
//	 animation = Pointer to the animation object.
//	 dt = Change in time (in seconds) since the last game loop.
void AnimationUpdate(AnimationPtr animation, float dt)
{
	if (animation)
	{
		animation->isDone = 0;
		if (!animation->isRunning)
		{
			return;
		}
		animation->frameDelay -= dt;
		if (animation->frameDelay <= 0)
		{
			AnimationAdvanceFrame(animation);
		}
		return;
	}
}

bool AnimationIsDone(AnimationPtr animation) 
{
	if (animation && animation->isDone)
		return true;
	return false;
}

void SetAnimationIsRunning(AnimationPtr animation, bool isRunning)
{
	if (animation)
	{
		animation->isRunning = isRunning;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void AnimationAdvanceFrame(AnimationPtr animation)
{
	if (animation)
	{
		animation->frameIndex += 1;
		if (animation->frameIndex >= animation->frameCount)
		{
			if (animation->isLooping)
			{
				animation->frameIndex = 0;
			}
			else
			{
				animation->frameIndex = animation->frameCount - 1;
				animation->isRunning = 0;
			}
			animation->isDone = 1;
		}
		if (animation->isRunning)
		{
			if (animation->sequence)
			{
				AnimationFramePtr AFrame = AnimationSequenceGetFrame(animation->sequence, animation->frameIndex);
				SpriteSetFrame(animation->sprite, AFrame->frameIndex);
				animation->frameDuration = AFrame->frameDuration;
			}
			else
			{
				SpriteSetFrame(animation->sprite, animation->frameIndex);
			}
			animation->frameDelay += animation->frameDuration;
		}
		else
		{
			animation->frameDelay = 0;
		}

	}
	return;
}
