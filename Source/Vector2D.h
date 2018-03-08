//------------------------------------------------------------------------------
//
// File Name:	Vector2D.h
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S18
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <AEEngine.h>

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Frequently, vector and matrix structures are declared publicly.  While an
// interface is typically provided with these structures, these are two common
// exceptions to the coding best practice of "hiding information".

// WARNING: Do not modify the declaration of this structure, as it is a part
// of the public interface.

typedef struct Vector2D
{
	// Position on the x-axis.
	float x;

	// Position on the y-axis.
	float y;

} Vector2D;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// This function sets the coordinates of the 2D vector (pResult) to 0
void Vector2DZero(AEVec2 *pResult);

// This function sets the coordinates of the 2D vector (pResult) to x & y
void Vector2DSet(AEVec2 *pResult, float x, float y);

// In this function, pResult will be set to the opposite of pVec0
void Vector2DNeg(AEVec2 *pResult, const AEVec2 *pVec0);

// In this function, pResult will be the sum of pVec0 and pVec1
void Vector2DAdd(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1);

// In this function, pResult will be the difference between pVec0 and pVec1 (specifically, pVec0 - pVec1)
void Vector2DSub(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1);

// In this function, pResult will be the unit vector of pVec0
void Vector2DNormalize(AEVec2 *pResult, const AEVec2 *pVec0);

// In this function, pResult will be the vector pVec0 scaled by the value 'scale'
void Vector2DScale(AEVec2 *pResult, const AEVec2 *pVec0, float scale);

// In this function, pResult will be the vector pVec0 scaled by 'scale' and added to pVec1
void Vector2DScaleAdd(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1, float scale);

// In this function, pResult will be the vector pVec0 scaled by 'scale' and pVec1 will be subtracted from it
void Vector2DScaleSub(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1, float scale);

// This function returns the length of the vector pVec0
float Vector2DLength(const AEVec2 *pVec0);

// This function returns the square of pVec0's length.
// NOTE: Do not use the square root function for this function.
float Vector2DSquareLength(const AEVec2 *pVec0);

// This function returns to distance between two points.
float Vector2DDistance(const AEVec2 *pVec0, const AEVec2 *pVec1);

// This function returns to distance between two points.
// NOTE: Do not use the square root function for this function.
float Vector2DSquareDistance(const AEVec2 *pVec0, const AEVec2 *pVec1);

// This function returns the dot product between pVec0 and pVec1
float Vector2DDotProduct(const AEVec2 *pVec0, const AEVec2 *pVec1);

// This function computes the coordinates of the unit vector represented by the angle "angle", which is in Degrees.
// Converting from degrees to radians can be performed as follows:
//	 radians = (angle * M_PI) / 180.0f
// M_PI is defined in "math.h", which may be included as follows:
//   #define _USE_MATH_DEFINES
//   #include <math.h>
void Vector2DFromAngleDeg(AEVec2 *pResult, float angle);

// This function computes the coordinates of the unit vector represented by the angle "angle", which is in Radians.
void Vector2DFromAngleRad(AEVec2 *pResult, float angle);

void Vector2DMul(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1);
//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

