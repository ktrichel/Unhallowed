#include "stdafx.h"
#include "Sprite.h"
#include "Mesh.h"
#include "SpriteSource.h"
#include "Physics.h"
#include "Trace.h"
#include "Matrix2D.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

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

  TransformPtr transform;

} Sprite;

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

// Dynamically allocate a new sprite object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (NOTE: Make sure to initialize the 'alpha' member variable to 1.0f.)
// Params:
//	 name = The name of the sprite.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
SpritePtr SpriteCreate(const char * name)
{
	SpritePtr NewSprite = calloc(1 , sizeof(Sprite));
	if (NewSprite)
	{
		NewSprite->name = name;
		NewSprite->alpha = 1;
		return NewSprite;
	}
	return NULL;
}

// Dynamically allocate a clone of an existing sprite.
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
SpritePtr SpriteClone(const SpritePtr other)
{
  if (other)
  {
    SpritePtr sprite = calloc(1, sizeof(Sprite));
    if (sprite)
    {
      *sprite = *other;
      return sprite;
    }
  }
  return NULL;
}

void SpriteFree(SpritePtr * sprite)
{
	if (sprite && *sprite)
	{
		free(*sprite);
		(*sprite) = NULL;
	}
}

void SpriteDraw(const SpritePtr sprite, TransformPtr transform) 
{
	if (sprite && sprite->mesh)
	{
		if (sprite->spriteSource == NULL)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxTextureSet(NULL, 0, 0);
		}
		else
		{
			float u = 0;
			float v = 0;

			SpriteSourceGetUV(sprite->spriteSource, sprite->frameIndex, &u, &v);

			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxTextureSet(SpriteSourceGetTexture(sprite->spriteSource), u, v);
		}
		AEGfxSetTransform(TransformGetMatrix(transform)->m);
		AEGfxSetTransparency(sprite->alpha);
		AEGfxSetBlendColor(0, 0, 0, 0);
		AEGfxMeshDraw(sprite->mesh, AE_GFX_MDM_TRIANGLES);
	}
}

void SpriteAdjustAlpha(SpritePtr sprite, float alphaAdjust)
{
	if (sprite)
		sprite->alpha = alphaAdjust;
}

void SpriteSetFrame(SpritePtr sprite, unsigned int frameIndex)
{
	TraceMessage("SpriteSetFrame: Level1 Sprite frame index = %i", frameIndex);
	if (sprite)
		sprite->frameIndex = frameIndex;
}

void SpriteSetMesh(SpritePtr sprite, AEGfxVertexList * mesh)
{
	if (sprite && mesh)
	{
		sprite->mesh = mesh;
	}
}

void SpriteSetSpriteSource(SpritePtr sprite, SpriteSourcePtr spriteSource)
{
	if (sprite && spriteSource)
	{
		sprite->spriteSource = spriteSource;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
