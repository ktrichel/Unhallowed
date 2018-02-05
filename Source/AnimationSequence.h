//------------------------------------------------------------------------------
//
// File Name:	AnimationSequence.h
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "AnimationFrame.h"

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef struct AnimationSequence * AnimationSequencePtr;

// An example of the structure to be defined in AnimationSequence.c:
#if 0
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
#endif

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new animation sequence object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Params:
//	 frameCount = The number of frames in the sequence.
//	 frameList = A pointer to an array of AnimationFrame records.
//	 isLooping = True if the animation loops, false otherwise.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
AnimationSequencePtr AnimationSequenceCreate(unsigned int frameCount, AnimationFramePtr frameList, bool isLooping);

// Free the memory associated with an animation sequence object.
// (Also, set the animation sequence pointer to NULL.)
// Params:
//	 sequence = Pointer to the animation sequence pointer.
void AnimationSequenceFree(AnimationSequencePtr * sequence);

// Get the specified frame information from the animation sequence.
// Params:
//	 sequence = Pointer to the animation sequence object.
//	 sequenceIndex = Desired offset into the animation sequence list.
// Returns:
//	 If the animation sequence pointer is valid,
//		then return the frame information at the specified offset,
//		else return a pointer to an 'empty' animation frame { 0, 0.0f },
const AnimationFramePtr AnimationSequenceGetFrame(AnimationSequencePtr sequence, unsigned int sequenceIndex);

// Get the maximum number of frames in the specified animation sequence.
// Params:
//	 sequence = Pointer to the animation sequence object.
// Returns:
//	 If the animation sequence pointer is valid,
//		then return the value in frameCount,
//		else return 0.
unsigned int AnimationSequenceGetFrameCount(AnimationSequencePtr sequence);

// Determine if the animation sequence is set to loop.
// Params:
//	 sequence = Pointer to the animation sequence object.
// Returns:
//	 If the animation sequence pointer is valid,
//		then return the value in isLooping,
//		else return false.
bool AnimationSequenceIsLooping(AnimationSequencePtr sequence);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

