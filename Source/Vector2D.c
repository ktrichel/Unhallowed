#include "stdafx.h"
#include "Matrix2D.h"
#define _USE_MATH_DEFINES
#include <AEEngine.h>
#include <math.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

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

// This function sets the coordinates of the 2D vector (pResult) to 0
void Vector2DZero(AEVec2 *pResult)
{
	if (pResult)
	{
		pResult->x = 0;
		pResult->y = 0;
	}
}

// This function sets the coordinates of the 2D vector (pResult) to x & y
void Vector2DSet(AEVec2 *pResult, float x, float y)
{
	if (pResult)
	{
		pResult->x = x;
		pResult->y = y;
	}
}

// In this function, pResult will be set to the opposite of pVec0
void Vector2DNeg(AEVec2 *pResult, const AEVec2 *pVec0)
{
	if (pResult && pVec0)
	{
		pResult->x = -pVec0->x;
		pResult->y = -pVec0->y;
	}
}

// In this function, pResult will be the sum of pVec0 and pVec1
void Vector2DAdd(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1)
{
	if (pResult && pVec0 && pVec1)
	{
		pResult->x = pVec0->x + pVec1->x;
		pResult->y = pVec0->y + pVec1->y;
	}
}

// In this function, pResult will be the difference between pVec0 and pVec1 (specifically, pVec0 - pVec1)
void Vector2DSub(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1)
{
	if (pResult && pVec0 && pVec1)
	{
		pResult->x = pVec0->x - pVec1->x;
		pResult->y = pVec0->y - pVec1->y;
	}

}

// In this function, pResult will be the unit vector of pVec0
void Vector2DNormalize(AEVec2 *pResult, const AEVec2 *pVec0)
{
	if (pResult && pVec0)
	{
		float lengthSquared = pVec0->x * pVec0->x + pVec0->y * pVec0->y;
		float length = (float)sqrt(lengthSquared);
		pResult->x = pVec0->x / length;
		pResult->y = pVec0->y / length;
	}
}

// In this function, pResult will be the vector pVec0 scaled by the value 'scale'
void Vector2DScale(AEVec2 *pResult, const AEVec2 *pVec0, float scale)
{
	if (pResult && pVec0)
	{
		pResult->x = pVec0->x * scale;
		pResult->y = pVec0->y * scale;
	}
}

// In this function, pResult will be the vector pVec0 scaled by 'scale' and added to pVec1
void Vector2DScaleAdd(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1, float scale)
{
	if (pResult && pVec0 && pVec1)
	{
		pResult->x = pVec1->x + pVec0->x * scale;
		pResult->y = pVec1->y + pVec0->y * scale;
		
	}
}

// In this function, pResult will be the vector pVec0 scaled by 'scale' and pVec1 will be subtracted from it
void Vector2DScaleSub(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1, float scale)
{
	if (pResult && pVec0 && pVec1)
	{
		pResult->x = -pVec1->x + pVec0->x * scale;
		pResult->y = -pVec1->y + pVec0->y * scale;

	}
}

// This function returns the length of the vector pVec0
float Vector2DLength(const AEVec2 *pVec0)
{
	if (pVec0)
	{
		float length = (float)sqrt(Vector2DSquareLength(pVec0));
		return length;
	}
	return 0;
}

// This function returns the square of pVec0's length.
// NOTE: Do not use the square root function for this function.
float Vector2DSquareLength(const AEVec2 *pVec0)
{
	if (pVec0)
	{
		float LengthSquare = pVec0->x * pVec0->x + pVec0->y * pVec0->y;
		return LengthSquare;
	}
	return 0;
}

// This function returns to distance between two points.
float Vector2DDistance(const AEVec2 *pVec0, const AEVec2 *pVec1)
{
	if (pVec0 && pVec1)
	{
		float distance = (float)sqrt(Vector2DSquareDistance(pVec0, pVec1));
		return distance;
	}
	return 0;
}

// This function returns to distance between two points.
// NOTE: Do not use the square root function for this function.
float Vector2DSquareDistance(const AEVec2 *pVec0, const AEVec2 *pVec1)
{
	if (pVec0 && pVec1)
	{
		float dist_x = pVec1->x - pVec0->x;
		float dist_y = pVec1->y - pVec0->y;
		float distanceSquared = dist_x * dist_x + dist_y * dist_y;
		return distanceSquared;
	}
	return 0;
}

// This function returns the dot product between pVec0 and pVec1
float Vector2DDotProduct(const AEVec2 *pVec0, const AEVec2 *pVec1)
{
	if (pVec0 && pVec1)
	{
		float DotProduct = pVec0->x * pVec1->x + pVec0->y * pVec1->y;
		return DotProduct;
	}
	return 0;
}

// This function computes the coordinates of the unit vector represented by the angle "angle", which is in Degrees.
// Converting from degrees to radians can be performed as follows:
//	 radians = (angle * M_PI) / 180.0f
// M_PI is defined in "math.h", which may be included as follows:
//   #define _USE_MATH_DEFINES
//   #include <math.h>
void Vector2DFromAngleDeg(AEVec2 *pResult, float angle)
{
	if (pResult)
	{
		float radian = (angle * (float)M_PI) / 180.0f;
		Vector2DFromAngleRad(pResult, radian);
	}
}
// This function computes the coordinates of the unit vector represented by the angle "angle", which is in Radians.
void Vector2DFromAngleRad(AEVec2 *pResult, float angle)
{
	if (pResult)
	{
		pResult->x = (float)cos(angle);
		pResult->y = (float)sin(angle);
	}
}

void Vector2DMul(AEVec2 *pResult, const AEVec2 *pVec0, const AEVec2 *pVec1)
{
	if (pResult && pVec0 && pVec1)
	{
		pResult->x = pVec0->x * pVec1->x;
		pResult->y = pVec0->y * pVec1->y;
	}

}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
