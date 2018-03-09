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
typedef struct AEMtx33 AEMtx33;
typedef struct Transform * TransformPtr;
typedef struct Physics * PhysicsPtr;

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

TransformPtr CreateTransform(void);

TransformPtr TransformCreate(float x, float y);

PhysicsPtr CreatePhysics(Vector2D OldTranslation, Vector2D Acceleration, Vector2D Velocity, float mass);

PhysicsPtr PhysicsClone(const PhysicsPtr other);

TransformPtr TransformClone(const TransformPtr other);

void TransformVelocity(TransformPtr transform, Vector2D velocity);

void PhysicsVelocity(PhysicsPtr physics, const Vector2D * velocity);

void FreePhysics(PhysicsPtr * physics);

void FreeTransform(TransformPtr * transform);

void PhysicsUpdate(PhysicsPtr physics, TransformPtr transform, float dt);

void PhysicsAcceleration(PhysicsPtr physics, Vector2D acceleration);

Vector2D GetOldTranslation(PhysicsPtr physics);

void SetPhysicsTranslation(PhysicsPtr physics, Vector2D translation);

void TransformSetScale(TransformPtr transform, Vector2D scale);

void TransformSetRotation(TransformPtr transform, float rotation);

PhysicsPtr PhysicsCreate(void);

void TransformSetRotation(TransformPtr transform, float rotation);

PhysicsPtr PhysicsCreate(void);

AEMtx33 * TransformGetMatrix(const TransformPtr transform);

const Vector2D * TransformGetTranslation(const TransformPtr transform);

void TransformSetTranslation(TransformPtr transform, const Vector2D * translation);

float TransformGetRotation(const TransformPtr transform);

Vector2D PhysicsGetVelocity(PhysicsPtr physics);

float PhysicsGetRotationalVelocity(PhysicsPtr physics);

void PhysicsSetRotationalVelocity(PhysicsPtr physics, float rotationalVelocity);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif
