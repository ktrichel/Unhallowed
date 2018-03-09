//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.h
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

#include "Vector2D.h"
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
// Public Macros:
//------------------------------------------------------------------------------

#define Matrix2DRowCol(pMtx, row, col) (pMtx)->m[(row)][(col)]

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

// Frequently, vector and matrix structures are declared publicly.  While an
// interface is typically provided with these structures, these are two common
// exceptions to the coding best practice of "hiding information".

// WARNING: Do not modify the declaration of this structure, as it is a part
// of the public interface.

typedef struct Matrix2D
{
	// The matrix is stored in column-major format, meaning the consecutive
	//   elements of columns are contiguous.
	//   m[row][column]
	float m[3][3];

} Matrix2D;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// This function sets the matrix equal to the identity matrix.
void Matrix2DIdentity(AEMtx33 *pResult);

// This function calculates the transpose matrix of Mtx and saves it in the result matrix.
// (NOTE: Care must be taken when pResult = pMtx.)
void Matrix2DTranspose(AEMtx33 *pResult, AEMtx33 *pMtx);

// This function multiplies Mtx0 with Mtx1 and saves the result in Result.
// Result = Mtx0*Mtx1
// (NOTE: Care must be taken when pResult = either pMtx0 or pMtx1.)
void Matrix2DConcat(AEMtx33 *pResult, AEMtx33 *pMtx0, AEMtx33 *pMtx1);

// This function creates a translation matrix from x & y and saves it in Result.
void Matrix2DTranslate(AEMtx33 *pResult, float x, float y);

// This function creates a scaling matrix from x & y and saves it in Result.
void Matrix2DScale(AEMtx33 *pResult, float x, float y);

// This matrix creates a rotation matrix from "Angle" whose value is in degrees.
// Save the resultant matrix in Result.
// Converting from degrees to radians can be performed as follows:
//	 radians = (angle * M_PI) / 180.0f
// M_PI is defined in "math.h", which may be included as follows:
//   #define _USE_MATH_DEFINES
//   #include <math.h>
void Matrix2DRotDeg(AEMtx33 *pResult, float angle);

// This matrix creates a rotation matrix from "Angle" whose value is in radians.
// Save the resultant matrix in Result.
void Matrix2DRotRad(AEMtx33 *pResult, float angle);

// This function multiplies the matrix Mtx with the vector Vec and saves the result in Result.
// Result = Mtx * Vec.
// (NOTE: Care must be taken when pResult = pVec.)
void Matrix2DMultVec(Vector2D *pResult, AEMtx33 *pMtx, Vector2D *pVec);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

