
#pragma once

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif
	typedef struct AEVec2 AEVec2;
	typedef struct BoundingBox * BoundingBoxPtr;

	BoundingBoxPtr CreateBoundingBox(AEVec2 position, AEVec2 halfsize);

	AEVec2 GetHalfSize(BoundingBoxPtr box);

	void UpdateBoundingBox(BoundingBoxPtr box, AEVec2 position);

	void FreeBoundingBox(BoundingBoxPtr * box);


#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif



