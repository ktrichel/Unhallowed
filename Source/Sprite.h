//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
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

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct AEGfxVertexList AEGfxVertexList;
typedef struct AEVec2 AEVec2;
typedef struct SpriteSource * SpriteSourcePtr;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

typedef struct Sprite * SpritePtr;

// An example of the structure to be defined in Sprite.c.
#if 0
// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct Sprite
{
	// The name of the sprite.
	const char * name;

	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The alpha transparency to use when drawing the sprite.
	float alpha;

	// The sprite source used when drawing (NULL = simple colored mesh).
	SpriteSourcePtr spriteSource;

	// The mesh used to draw the sprite.
	AEGfxVertexList * mesh;

} Sprite;
#endif

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new sprite object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (NOTE: Make sure to initialize the 'alpha' member variable to 1.0f.)
// Params:
//	 name = The name of the sprite.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
SpritePtr SpriteCreate(const char * name);

// Free the memory associated with a sprite object.
// (Also, set the sprite pointer to NULL.)
// Params:
//	 sprite = Pointer to the sprite pointer.
void SpriteFree(SpritePtr * sprite);

// Draw a sprite (Sprite can be textured or untextured).
// Params:
//	 sprite = Pointer to the sprite object.
//   position = The world position of the sprite.
void SpriteDraw(const SpritePtr sprite, AEVec2 position);

// Adjust a sprite's alpha up/down.
// (NOTE: Make sure to clamp the resulting alpha value between 0.0f and 1.0f.)
// Params:
//	 sprite = Pointer to the sprite object.
//   alphaAdjust = Offset to apply to the sprite's 'alpha' value.
void SpriteAdjustAlpha(SpritePtr sprite, float alphaAdjust);

// Set the sprite's current frame.
// (NOTE: You must validate the frame index against the sprite source's frame count.)
// Params:
//	 sprite = Pointer to the sprite object.
//   frameIndex = New frame index for the sprite (0 .. frame count).
// ADDITIONAL REQUIREMENTS:
//   This function must make the following function call:
//     TraceMessage("SpriteSetFrame: %s frame index = %d", sprite->name, frameIndex);
void SpriteSetFrame(SpritePtr sprite, unsigned int frameIndex);

// Set the sprite's mesh.
// (NOTE: This mesh may be textured or untextured.)
// (NOTE: This mesh may contain any number of triangles.)
// Params:
//	 sprite = Pointer to the sprite object.
//   mesh = Pointer to a mesh created using the Alpha Engine.
void SpriteSetMesh(SpritePtr sprite, AEGfxVertexList * mesh);

// Set a new SpriteSource for the specified sprite.
// Params:
//	 sprite = Pointer to the sprite to be modified.
//	 spriteSource = A new sprite source for the sprite.
void SpriteSetSpriteSource(SpritePtr sprite, SpriteSourcePtr spriteSource);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

