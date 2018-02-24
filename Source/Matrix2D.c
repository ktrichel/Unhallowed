#include "stdafx.h"
#include "Matrix2D.h"
#define _USE_MATH_DEFINES
#include <math.h>

// This function sets the matrix equal to the identity matrix.
void Matrix2DIdentity(AEMtx33 *pResult)
{
	if (pResult)
	{
		int x;
		int y;
		for (x = 0; x < 3; ++x)
		{
			for (y = 0; y < 3; ++y)
			{
				pResult->m[x][y] = 0;
			}
		}
		pResult->m[0][0] = 1;
		pResult->m[1][1] = 1;
		pResult->m[2][2] = 1;

	}
}

// This function calculates the transpose matrix of Mtx and saves it in the result matrix.
// (NOTE: Care must be taken when pResult = pMtx.)
void Matrix2DTranspose(AEMtx33 *pResult, AEMtx33 *pMtx)
{
	int x = 0;
	int y = 0;
	float temp = 0;

	if (pResult && pMtx)
	{
		for (x = 0; x < 3; ++x)
		{
			for (y = 0; y < 3; ++y)
			{
				temp = pMtx->m[x][y];
				pResult->m[y][x] = temp;
			}
		}

	}
}

// This function multiplies Mtx0 with Mtx1 and saves the result in Result.
// Result = Mtx0*Mtx1
// (NOTE: Care must be taken when pResult = either pMtx0 or pMtx1.)
void Matrix2DConcat(AEMtx33 *pResult, AEMtx33 *pMtx0, AEMtx33 *pMtx1)
{
	int x = 0;
	int y = 0;
	float temp = 0;
	AEMtx33 tempMatrix = { 0 };
	if (pResult && pMtx0 && pMtx1)
	{
		for (x = 0; x < 3; ++x)
		{
			for (y = 0; y < 3; ++y)
			{

				temp = pMtx0->m[x][0] * pMtx1->m[0][y] +
					   pMtx0->m[x][1] * pMtx1->m[1][y] +
					   pMtx0->m[x][2] * pMtx1->m[2][y];
				tempMatrix.m[x][y] = temp;
			}
		}
		*pResult = tempMatrix;
	}
}

// This function creates a translation matrix from x & y and saves it in Result.
void Matrix2DTranslate(AEMtx33 *pResult, float x, float y)
{
	if (pResult)
	{
		Matrix2DIdentity(pResult);

		pResult->m[0][2] = x;
		pResult->m[1][2] = y;
	}
}
// This function creates a scaling matrix from x & y and saves it in Result.
void Matrix2DScale(AEMtx33 *pResult, float x, float y)
{
	if (pResult)
	{
		Matrix2DIdentity(pResult);
		pResult->m[0][0] = x;
		pResult->m[1][1] = y;
	}
}

// This matrix creates a rotation matrix from "Angle" whose value is in degrees.
// Save the resultant matrix in Result.
// Converting from degrees to radians can be performed as follows:
//	 radians = (angle * M_PI) / 180.0f
// M_PI is defined in "math.h", which may be included as follows:
//   #define _USE_MATH_DEFINES
//   #include <math.h>
void Matrix2DRotDeg(AEMtx33 *pResult, float angle)
{
	if (pResult)
	{
		float radians = 0;
		radians = (angle * (float)M_PI) / 180.f;
		Matrix2DRotRad(pResult, radians);
	}
}
// This matrix creates a rotation matrix from "Angle" whose value is in radians.
// Save the resultant matrix in Result.
void Matrix2DRotRad(AEMtx33 *pResult, float angle)
{
	if (pResult)
	{
		Matrix2DIdentity(pResult);
		pResult->m[0][0] = (float)cos(angle);
		pResult->m[0][1] = -(float)sin(angle);
		pResult->m[1][0] = (float)sin(angle);
		pResult->m[1][1] = (float)cos(angle);
	}

}
// This function multiplies the matrix Mtx with the vector Vec and saves the result in Result.
// Result = Mtx * Vec.
// (NOTE: Care must be taken when pResult = pVec.)
void Matrix2DMultVec(AEVec2 *pResult, AEMtx33 *pMtx, AEVec2 *pVec)
{
	if (pResult && pMtx && pVec)
	{
		pResult->x = pMtx->m[0][0] * pVec->x + pMtx->m[0][1] * pVec->y + pMtx->m[0][2];
		pResult->y = pMtx->m[1][0] * pVec->x + pMtx->m[1][1] * pVec->y + pMtx->m[1][2];
	}
}