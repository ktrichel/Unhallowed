#include "stdafx.h"
#include "SpriteSource.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SpriteSource
{
	// The dimensions of the sprite sheet.
	int	numRows;
	int	numCols;

	// Pointer to a texture created using the Alpha Engine.
	AEGfxTexturePtr	pTexture;

} SpriteSource;

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

SpriteSourcePtr SpriteSourceCreate(int numCols, int numRows, AEGfxTexturePtr pTexture)
{
	SpriteSourcePtr NewSource = calloc(1, sizeof(SpriteSource));

	if (NewSource)
	{
		NewSource->numRows = numRows;
		NewSource->numCols = numCols;
		NewSource->pTexture = pTexture;
		return NewSource;
	}
	return NULL;
}

void SpriteSourceFree(SpriteSourcePtr * spriteSource)
{
	if (spriteSource && *spriteSource)
	{
		free(*spriteSource);
		(*spriteSource) = NULL;
	}
}

AEGfxTexturePtr SpriteSourceGetTexture(SpriteSourcePtr spriteSource)
{
	if (spriteSource)
		return spriteSource->pTexture;
	return NULL;
}

unsigned int SpriteSourceGetFrameCount(SpriteSourcePtr spriteSource)
{
	if (spriteSource)
	{
		return spriteSource->numCols * spriteSource->numRows;
	}

	return 0;
}

void SpriteSourceGetUV(SpriteSourcePtr spriteSource, unsigned int frameIndex, float * u, float * v)
{
	if (spriteSource)
	{
		*u = (1.0f / spriteSource->numCols) * (frameIndex % spriteSource->numCols);
		*v = (1.0f / spriteSource->numRows) * (frameIndex / spriteSource->numRows);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
