
#pragma once

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif
	typedef struct AEVec2 AEVec2;
	typedef struct BoundingBox * BoundingBoxPtr;

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


#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif



