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

PhysicsPtr CreatePhysics(AEVec2 OldTranslation, AEVec2 Acceleration, AEVec2 Velocity, float mass);

void TransformVelocity(TransformPtr transform, AEVec2 velocity);

void PhysicsVelocity(PhysicsPtr physics, AEVec2 velocity);

void FreePhysics(PhysicsPtr * physics);

void FreeTransform(TransformPtr * transform);

void PhysicsUpdate(PhysicsPtr physics, TransformPtr transform, float dt);

void PhysicsAcceleration(PhysicsPtr physics, AEVec2 acceleration);

AEVec2 GetOldTranslation(PhysicsPtr physics);

void SetPhysicsTranslation(PhysicsPtr physics, AEVec2 translation);

void TransformSetScale(TransformPtr transform, AEVec2 scale);

void TransformSetRotation(TransformPtr transform, float rotation);

PhysicsPtr PhysicsCreate(void);

void TransformSetRotation(TransformPtr transform, float rotation);

PhysicsPtr PhysicsCreate(void);

AEMtx33 * TransformGetMatrix(const TransformPtr transform);

const AEVec2 * TransformGetTranslation(const TransformPtr transform);

void TransformSetTranslation(TransformPtr transform, const AEVec2 * translation);

float TransformGetRotation(const TransformPtr transform);

AEVec2 PhysicsGetVelocity(PhysicsPtr physics);
//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif
