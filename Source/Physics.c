#include "stdafx.h"
#include "Physics.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Transform
{
	AEVec2 translation;
	float rotation;
	AEVec2 scale;

	AEMtx33 matrix;

	bool isDirty;
}Transform;

typedef struct Physics
{
	AEVec2 oldTranslation;
	AEVec2 acceleration;
	AEVec2 velocity;
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
		physics->oldTranslation = transform->translation;
		physics->velocity.x += physics->acceleration.x * dt;
		physics->velocity.y += physics->acceleration.y * dt;
		physics->oldTranslation.x += physics->velocity.x * dt;
		physics->oldTranslation.y += physics->velocity.y * dt;
        AEGfxSetCamPosition(transform->translation.x, transform->translation.y);
		transform->translation = physics->oldTranslation;
	}

}

void PhysicsAcceleration(PhysicsPtr physics, float x_acceleration, float y_acceleration)
{
	if (physics)
	{
		physics->acceleration.x = x_acceleration;
		physics->acceleration.y = y_acceleration;
	}
}

// previous implementation of create physics, you can use setters instead but I'm leaving the code
// here so it can run before I continue cleaning things up
// !!! DO NOT CALL THIS !!!
PhysicsPtr CreatePhysics(AEVec2 OldTranslation, AEVec2 Acceleration, AEVec2 Velocity, float mass)
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

void TransformVelocity(TransformPtr transform, float x, float y)
{
	if (transform)
	{
		transform->translation.x += x;
		transform->translation.y += y;
    AEGfxSetCamPosition(transform->translation.x, transform->translation.y);
	}
}

void PhysicsVelocity(PhysicsPtr physics, float x, float y)
{
	if (physics)
	{
		physics->velocity.x = x;
		physics->velocity.y = y;
	}
}
AEVec2 GetOldTranslation(PhysicsPtr physics)
{
	AEVec2 empty = { 0 };
	if (physics)
	{
		return physics->oldTranslation;
	}
	return empty;
}

void SetPhysicsTranslation(PhysicsPtr physics, AEVec2 translation)
{
  if (physics)
  {
    physics->oldTranslation.x = translation.x;
    physics->oldTranslation.y = translation.y;
  }
}

void SetTranslation(TransformPtr transform, float x, float y)
{
  if (transform)
  {
    transform->translation.x = x;
    transform->translation.y = y;
  }
}

void TransformSetScale(TransformPtr transform, AEVec2 scale)
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

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
