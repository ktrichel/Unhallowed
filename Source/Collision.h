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

typedef struct Vector2D Vector2D;
typedef struct BoundingBox * BoundingBoxPtr;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

BoundingBoxPtr CreateBoundingBox(Vector2D position, Vector2D halfsize);

Vector2D GetHalfSize(BoundingBoxPtr box);

	bool CollisionCheck(BoundingBoxPtr box1, BoundingBoxPtr box2);

	bool CollisionCheckTop(BoundingBoxPtr box1, BoundingBoxPtr box2);

bool CollisionCheckRight(BoundingBoxPtr box1, BoundingBoxPtr box2);

bool CollisionCheckDown(BoundingBoxPtr box1, BoundingBoxPtr box2);

bool CollisionCheckLeft(BoundingBoxPtr box1, BoundingBoxPtr box2);

// updates the position of the bounding box
void UpdateBoundingBox(BoundingBoxPtr box, Vector2D position);

void FreeBoundingBox(BoundingBoxPtr * box);

void HalfsizeScale(BoundingBoxPtr box, Vector2D scale);

int CollisionCheckCollidedSide(BoundingBoxPtr box1, BoundingBoxPtr box2);
//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif