#include "stdafx.h"
#include "Collision.h"
#include <AEEngine.h>

typedef struct BoundingBox
{
	AEVec2 Position;
	AEVec2 HalfSize;
} BoundingBox;

BoundingBoxPtr CreateBoundingBox(AEVec2 position, AEVec2 halfsize)
{
	BoundingBoxPtr box = calloc(1, sizeof(BoundingBox));
	box->Position = position;
	box->HalfSize = halfsize;

	return box;
}

AEVec2 GetHalfSize(BoundingBoxPtr box)
{
	AEVec2 empty = { 0 };
	if (box)
	{
		return box->HalfSize;
	}
	return empty;
}

void UpdateBoundingBox(BoundingBoxPtr box, AEVec2 position)
{
	if (box)
	{
		box->Position = position;
	}
}

void FreeBoundingBox(BoundingBoxPtr * box)
{
	free(*box);
	*box = NULL;
}