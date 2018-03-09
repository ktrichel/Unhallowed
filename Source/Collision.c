#include "stdafx.h"
#include "Collision.h"
#include "Vector2D.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct BoundingBox
{
	Vector2D Position;
	Vector2D HalfSize;
} BoundingBox;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

enum sides { cTop, cRight, cBottom, cLeft };

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

BoundingBoxPtr CreateBoundingBox(Vector2D position, Vector2D halfsize)
{
	BoundingBoxPtr box = calloc(1, sizeof(BoundingBox));
	box->Position = position;
	box->HalfSize = halfsize;

	return box;
}

Vector2D GetHalfSize(BoundingBoxPtr box)
{
	Vector2D empty = { 0 };
	if (box)
	{
		return box->HalfSize;
	}
	return empty;
}

void UpdateBoundingBox(BoundingBoxPtr box, Vector2D position)
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
	if (box1 && box2)
	{
		float box1_xMax = box1->Position.x + box1->HalfSize.x;
		float box1_xMin = box1->Position.x - box1->HalfSize.x;
		float box1_yMax = box1->Position.y + box1->HalfSize.y;
		float box1_yMin = box1->Position.y - box1->HalfSize.y;

		float box2_xMax = box2->Position.x + box2->HalfSize.x;
		float box2_xMin = box2->Position.x - box2->HalfSize.x;
		float box2_yMax = box2->Position.y + box2->HalfSize.y;
		float box2_yMin = box2->Position.y - box2->HalfSize.y;

		if (box1_xMax < box2_xMin || box1_xMin > box2_xMax)
			return false;
		if (box1_yMax < box2_yMin || box1_yMin > box2_yMax)
			return false;

		/*
		if (box2->Position.x + box2->HalfSize.x < box1->Position.x)
			return false;
		if (box1->Position.x + box1->HalfSize.x < box2->Position.x)
			return false;


		if (box2->Position.y + box2->HalfSize.y < box1->Position.y)
			return false;
		if (box1->Position.y + box1->HalfSize.y < box2->Position.y)
			return false;
		*/
	}
	return true;
}

// call after a collision has been confirmed
// finds the distance between the bounding boxes
// and determines which cardinal direction (NESW)
// is being collided into
// returns an int 
int CollisionCheckCollidedSide(BoundingBoxPtr box1, BoundingBoxPtr box2)
{
	if (box1 && box2)
	{
		float box1_xMax = box1->Position.x + box1->HalfSize.x;
		float box1_xMin = box1->Position.x - box1->HalfSize.x;
		float box1_yMax = box1->Position.y + box1->HalfSize.y;
		float box1_yMin = box1->Position.y - box1->HalfSize.y;

		float box2_xMax = box2->Position.x + box2->HalfSize.x;
		float box2_xMin = box2->Position.x - box2->HalfSize.x;
		float box2_yMax = box2->Position.y + box2->HalfSize.y;
		float box2_yMin = box2->Position.y - box2->HalfSize.y;


		float xMinMax_Distance = box1_xMin - box2_xMax; // distance between box1 left point and box2 right point
		float xMaxMin_Distance = box1_xMax - box2_xMin; // distance between box1 right point and box2 left point

		float yMinMax_Distance = box1_yMin - box2_yMax; // distance between box1 bottom point and box2 top point
		float yMaxMin_Distance = box1_yMax - box2_yMin; // distance between box1 top point and box2 bottom point

		// if the values are negative, changes them to positive
		// acts like an absolute value as you can't have a negative distance
		if (xMinMax_Distance < 0)
			xMinMax_Distance *= -1;
		if (xMaxMin_Distance < 0)
			xMaxMin_Distance *= -1;

		if (yMinMax_Distance < 0)
			yMinMax_Distance *= -1;
		if (yMaxMin_Distance < 0)
			yMaxMin_Distance *= -1;

		if (yMinMax_Distance <= yMaxMin_Distance &&
			yMinMax_Distance <= xMaxMin_Distance &&
			yMinMax_Distance <= xMinMax_Distance)
			return cTop;

		if (xMinMax_Distance <= xMaxMin_Distance &&
			xMinMax_Distance <= yMinMax_Distance &&
			xMinMax_Distance <= yMaxMin_Distance)
			return cRight;

		if (yMaxMin_Distance <= yMinMax_Distance &&
			yMaxMin_Distance <= xMaxMin_Distance &&
			xMinMax_Distance <= xMinMax_Distance)
			return cBottom;

		if (xMaxMin_Distance <= xMinMax_Distance &&
			xMaxMin_Distance <= yMinMax_Distance &&
			xMaxMin_Distance <= yMaxMin_Distance)
			return cLeft;
	}
	return -1;
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

void HalfsizeScale(BoundingBoxPtr box, Vector2D scale)
{
	if (box)
	{
		box->HalfSize.x *= scale.x;
		box->HalfSize.y *= scale.y;
	}
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
