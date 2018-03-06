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

typedef struct AEVec2 AEVec2;
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

BoundingBoxPtr CreateBoundingBox(AEVec2 position, AEVec2 halfsize);

AEVec2 GetHalfSize(BoundingBoxPtr box);

	bool CollisionCheck(BoundingBoxPtr box1, BoundingBoxPtr box2);

	bool CollisionCheckTop(BoundingBoxPtr box1, BoundingBoxPtr box2);

bool CollisionCheckRight(BoundingBoxPtr box1, BoundingBoxPtr box2);

bool CollisionCheckDown(BoundingBoxPtr box1, BoundingBoxPtr box2);

bool CollisionCheckLeft(BoundingBoxPtr box1, BoundingBoxPtr box2);

// updates the position of the bounding box
void UpdateBoundingBox(BoundingBoxPtr box, AEVec2 position);

void FreeBoundingBox(BoundingBoxPtr * box);

void HalfsizeScale(BoundingBoxPtr box, AEVec2 scale);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif