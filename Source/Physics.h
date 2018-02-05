
#pragma once

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

typedef struct AEVec2 AEVec2;
typedef struct Transform * TransformPtr;
typedef struct Physics * PhysicsPtr;

TransformPtr CreateTransform(void);

PhysicsPtr CreatePhysics(AEVec2 OldTranslation, AEVec2 Acceleration, AEVec2 Velocity, float mass);

void TransformVelocity(TransformPtr transform, float x, float y);

void FreePhysics(PhysicsPtr * physics);

void FreeTransform(TransformPtr * transform);

void PhysicsUpdate(PhysicsPtr physics, TransformPtr transform, float dt);

AEVec2 GetOldTranslation(PhysicsPtr physics);



#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif
