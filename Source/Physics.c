#include "stdafx.h"
#include "Physics.h"
#include "Matrix2D.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Transform
{
	Vector2D translation;
	float rotation;
	Vector2D scale;

	AEMtx33 matrix;

	bool isDirty;
}Transform;

typedef struct Physics
{
	Vector2D oldTranslation;
	Vector2D acceleration;
	Vector2D velocity;
  float rotationalVelocity;
  float inverseMass;
}Physics;

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

void PhysicsUpdate(PhysicsPtr physics, TransformPtr transform, float dt)
{
	if (physics && transform)
	{
		physics->oldTranslation = *TransformGetTranslation(transform);
		Vector2D newtranslation = physics->oldTranslation;
		Vector2DScaleAdd(&physics->velocity, &physics->acceleration, &physics->velocity, dt);
		Vector2DScaleAdd(&newtranslation, &physics->velocity, &physics->oldTranslation, dt);

		const Vector2D * translate = &newtranslation;
		float rotation = TransformGetRotation(transform);

		TransformSetRotation(transform, rotation);
		TransformSetTranslation(transform, translate);
	}

}

void PhysicsAcceleration(PhysicsPtr physics, Vector2D acceleration)
{
	if (physics)
	{
		physics->acceleration.x = acceleration.x;
		physics->acceleration.y = acceleration.y;
	}
}

// previous implementation of create physics, you can use setters instead but I'm leaving the code
// here so it can run before I continue cleaning things up
// !!! DO NOT CALL THIS !!!
PhysicsPtr CreatePhysics(Vector2D OldTranslation, Vector2D Acceleration, Vector2D Velocity, float mass)
{
	PhysicsPtr physics = calloc(1, sizeof(Physics));
	if (physics)
	{
		physics->oldTranslation = OldTranslation;
		physics->acceleration = Acceleration;
		physics->velocity = Velocity;
		physics->inverseMass = 1.0f / mass;
		return physics;
	}
	return NULL;
}


// Dynamically allocate a new physics component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
PhysicsPtr PhysicsCreate(void)
{
	PhysicsPtr physics = calloc(1, sizeof(Physics));
	if (physics)
	{
		return physics;
	}
	return NULL;
}

// Dynamically allocate a new transform object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: Failing to initialize the scale values to non-zero values will result in invisible sprites.)
// Params:
//	 x = Initial world position on the x-axis.
//	 y = Initial world position on the y-axis.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
TransformPtr TransformCreate(float x, float y)
{
	TransformPtr transform = calloc(1, sizeof(Transform));

	if (transform)
	{
		transform->translation.x = x;
		transform->translation.y = y;
		return transform;
	}
	return NULL;
}

TransformPtr CreateTransform(void)
{
	TransformPtr transform = calloc(1, sizeof(Transform));
	if (transform)
		return transform;
	return NULL;
}

// Dynamically allocate a clone of an existing physics component.
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
PhysicsPtr PhysicsClone(const PhysicsPtr other)
{
  if (other)
  {
    PhysicsPtr physics = calloc(1, sizeof(Physics));
    if (physics)
    {
      *physics = *other;
      return physics;
    }
  }
  return NULL;
}

// Dynamically allocate a clone of an existing transform.
// Params:
//	 other = Pointer to the component to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned component,
//	   else return NULL.
TransformPtr TransformClone(const TransformPtr other)
{
  if (other)
  {
    TransformPtr transform = calloc(1, sizeof(Transform));
    if (transform)
    {
      *transform = *other;
      return transform;
    }
  }
  return NULL;
}

void FreeTransform(TransformPtr * transform)
{
	free(*transform);
	*transform = NULL;
}

void FreePhysics(PhysicsPtr * physics)
{
	free(*physics);
	*physics = NULL;
}

void TransformVelocity(TransformPtr transform, Vector2D velocity)
{
	if (transform)
	{
		Vector2DAdd(&transform->translation, &transform->translation, &velocity);
		AEGfxSetCamPosition(transform->translation.x, transform->translation.y);
	}
}

void PhysicsVelocity(PhysicsPtr physics, const Vector2D *velocity)
{
	if (physics)
	{
		physics->velocity = *velocity;
	}
}
Vector2D GetOldTranslation(PhysicsPtr physics)
{
	Vector2D empty = { 0 };
	if (physics)
	{
		return physics->oldTranslation;
	}
	return empty;
}

void SetPhysicsTranslation(PhysicsPtr physics, Vector2D translation)
{
  if (physics)
  {
	  physics->oldTranslation = translation;
  }
}
// Set the translation of a transform component.
// Params:
//	 transform = Pointer to the transform component.
//	 translation = Pointer to a translation vector.
void TransformSetTranslation(TransformPtr transform, const Vector2D * translation)
{
	if (transform && translation)
	{
		transform->translation.x = translation->x;
		transform->translation.y = translation->y;
		transform->isDirty = true;
	}
}

void TransformSetScale(TransformPtr transform, Vector2D scale)
{
	if (transform)
	{
		transform->scale = scale;
	}
}

void TransformSetRotation(TransformPtr transform, float rotation)
{
	if (transform)
	{
		transform->rotation = rotation;
	}
}

// Get the transform matrix, based upon translation, rotation and scale settings.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's matrix structure,
//		else return a NULL pointer.
AEMtx33 * TransformGetMatrix(const TransformPtr transform)
{
	if (transform)
	{
		if (transform->isDirty)
		{
			AEMtx33 translate;
			AEMtx33 rotate;
			AEMtx33 scale;

			Matrix2DTranslate(&translate, transform->translation.x, transform->translation.y);
			Matrix2DScale(&scale, transform->scale.x, transform->scale.y);
			Matrix2DRotRad(&rotate, transform->rotation);

			Matrix2DConcat(&transform->matrix, &rotate, &scale);
			Matrix2DConcat(&transform->matrix, &translate, &transform->matrix);
			transform->isDirty = false;
		}
		return &transform->matrix;
	}
	return NULL;
}

// Get the translation of a transform component.
// Params:
//	 transform = Pointer to the transform object.
// Returns:
//	 If the transform pointer is valid,
//		then return a pointer to the component's translation structure,
//		else return a NULL pointer.
const Vector2D * TransformGetTranslation(const TransformPtr transform)
{
	if (transform)
	{
		return &transform->translation;
	}
	return NULL;
}

float TransformGetRotation(const TransformPtr transform)
{
	if (transform)
	{
		return transform->rotation;
	}
	return 0;
}

Vector2D PhysicsGetVelocity(PhysicsPtr physics)
{
	Vector2D Empty = { 0 };
	if (physics)
	{
		return physics->velocity;
	}
	return Empty;
}

// Get the rotational velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return the component's rotational velocity value,
//		else return 0.0f.
float PhysicsGetRotationalVelocity(PhysicsPtr physics)
{
  if (physics)
  {
    return physics->rotationalVelocity;
  }
  return 0.0f;
}

// Set the rotational velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
//	 rotationalVelocity = The new rotational velocity.
void PhysicsSetRotationalVelocity(PhysicsPtr physics, float rotationalVelocity)
{
  if (physics)
  {
    physics->rotationalVelocity = rotationalVelocity;
  }
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
