#include "stdafx.h"
#include "AnimationSequence.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct AnimationSequence
{
	// The number of frames in the animation sequence.
	unsigned int frameCount;

	// A pointer to an array of AnimationFrame records.
	AnimationFramePtr frameList;

	// True if the animation loops, false otherwise.
	bool isLooping;

} AnimationSequence;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

AnimationSequencePtr AnimationSequenceCreate(unsigned int frameCount, AnimationFramePtr frameList, bool isLooping)
{
	AnimationSequencePtr AniSequence = calloc(1, sizeof(AnimationSequence));
	if (AniSequence)
	{
		AniSequence->frameCount = frameCount;
		AniSequence->frameList = frameList;
		AniSequence->isLooping = isLooping;

		return AniSequence;
	}
	return NULL;
}

void AnimationSequenceFree(AnimationSequencePtr * sequence)
{
	if (sequence && *sequence)
	{
		free(*sequence);
		(*sequence) = NULL;
	}
}

const AnimationFramePtr AnimationSequenceGetFrame(AnimationSequencePtr sequence, unsigned int sequenceIndex)
{
	const AnimationFramePtr empty = { 0 };
	if (sequence)
	{
		return &sequence->frameList[sequenceIndex];
	}
	else
		return empty;
}

unsigned int AnimationSequenceGetFrameCount(AnimationSequencePtr sequence)
{
	if (sequence)
		return sequence->frameCount;
	return 0;
}

bool AnimationSequenceIsLooping(AnimationSequencePtr sequence)
{
	if (sequence && sequence->isLooping)
		return true;
	return false;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
