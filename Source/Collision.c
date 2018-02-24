#include "stdafx.h"
#include "Collision.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct BoundingBox
{
	AEVec2 Position;
	AEVec2 HalfSize;
} BoundingBox;

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

bool CollisionCheck(BoundingBoxPtr box1, BoundingBoxPtr box2)
{
	if (CollisionCheckTop(box1, box2))
		return 1;
	if (CollisionCheckRight(box1, box2))
		return 1;
	if (CollisionCheckDown(box1, box2))
		return 1;
	if (CollisionCheckLeft(box1, box2))
		return 1;

	return 0;
}

bool CollisionCheckTop(BoundingBoxPtr box1, BoundingBoxPtr box2)
{
	if (box1 && box2)
	{
		if (box1->Position.y - box1->HalfSize.y <= box2->Position.y + box2->HalfSize.y &&
			box1->Position.x - box1->HalfSize.x <= box2->Position.x + box2->HalfSize.x &&
			box1->Position.x + box1->HalfSize.x >= box2->Position.x - box2->HalfSize.x)
		{
			return 1;
		}
	}
	return 0;
}

bool CollisionCheckRight(BoundingBoxPtr box1, BoundingBoxPtr box2)
{
	if (box1 && box2)
	{
		if (box1->Position.x - box1->HalfSize.x <= box2->Position.x + box2->HalfSize.x &&
			box1->Position.y + box1->HalfSize.y >= box2->Position.y - box2->HalfSize.y &&
			box1->Position.y - box1->HalfSize.y <= box2->Position.y + box2->HalfSize.y)
		{
			return 1;
		}
	}
	return 0;
}

bool CollisionCheckDown(BoundingBoxPtr box1, BoundingBoxPtr box2)
{
	if (box1 && box2)
	{
		if (box1->Position.y + box1->HalfSize.y >= box2->Position.y - box2->HalfSize.y &&
			box1->Position.x + box1->HalfSize.x >= box2->Position.x - box2->HalfSize.x &&
			box1->Position.x - box1->HalfSize.x <= box2->Position.x + box2->HalfSize.x)
		{
			return 1;
		}
	}
	return 0;
}

bool CollisionCheckLeft(BoundingBoxPtr box1, BoundingBoxPtr box2)
{
	if (box1 && box2)
	{
		if (box1->Position.x + box1->HalfSize.x >= box2->Position.x - box2->HalfSize.x &&
			box1->Position.y - box1->HalfSize.y <= box2->Position.y + box2->HalfSize.y &&
			box1->Position.y + box1->HalfSize.y >= box2->Position.y - box2->HalfSize.y)
		{
			return 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
