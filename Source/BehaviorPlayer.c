//------------------------------------------------------------------------------
//
// File Name:	BehaviorPlayer.c
// Author(s):	Kyle Trichel (kyle.trichel)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorPlayer.h"
#include "Behavior.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "BehaviorBullet.h"
#include "GameObjectManager.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

enum Ship
{
  cSpaceshipInvalid,
  cSpaceshipIdle,
  cSpaceshipThrust
};

static const float spaceshipAcceleration = 150.0f;
static const float spaceshipSpeedMax = 500.0f;
static const float spaceshipTurnRateMax = PI / 1.5f;
static const float spaceshipWeaponCooldownTime = 0.032f;
static const float spaceshipWeaponBulletSpeed = 750.0f;


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
static void BehaviorPlayerUpdateRotation(BehaviorPtr behavior, float dt);
static void BehaviorPlayerUpdateVelocity(BehaviorPtr behavior, float dt);
static void BehaviorPlayerUpdateWeapon(BehaviorPtr behavior, float dt);
static void BehaviorPlayerSpawnBullet(BehaviorPtr behavior);


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (Spaceship) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
BehaviorPtr BehaviorPlayerCreate(void)
{
  BehaviorPtr behavior = calloc(1, sizeof(Behavior));
  if (behavior)
  {
    behavior->stateCurr = cSpaceshipInvalid;
    behavior->stateNext = cSpaceshipIdle;
    behavior->onInit = BehaviorPlayerInit;
    behavior->onExit = BehaviorPlayerExit;
    behavior->onUpdate = BehaviorPlayerUpdate;

    return behavior;
  }
  return NULL;
}

// Initialize the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
void BehaviorPlayerInit(BehaviorPtr behavior)
{
  UNREFERENCED_PARAMETER(behavior);
}

// Update the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorPlayerUpdate(BehaviorPtr behavior, float dt)
{
  switch (behavior->stateCurr)
  {
  case cSpaceshipIdle:
    BehaviorPlayerUpdateRotation(behavior, dt);
    BehaviorPlayerUpdateWeapon(behavior, dt);
    if (AEInputCheckTriggered(VK_UP))
    {
      behavior->stateNext = cSpaceshipThrust;
    }
    break;
  case cSpaceshipThrust:
    BehaviorPlayerUpdateRotation(behavior, dt);
    BehaviorPlayerUpdateVelocity(behavior, dt);
    BehaviorPlayerUpdateWeapon(behavior, dt);
    if (!AEInputCheckCurr(VK_UP))
    {
      behavior->stateNext = cSpaceshipIdle;
    }
    break;
  default:
    break;
  }
}

// Exit the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorPlayerExit(BehaviorPtr behavior)
{
  UNREFERENCED_PARAMETER(behavior);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void BehaviorPlayerUpdateRotation(BehaviorPtr behavior, float dt)
{
  UNREFERENCED_PARAMETER(dt);

  PhysicsPtr physics = GameObjectGetPhysics(behavior->parent);

  if (AEInputCheckCurr(VK_LEFT))
  {
    PhysicsSetRotationalVelocity(physics, spaceshipTurnRateMax);
  }
  else if (AEInputCheckCurr(VK_RIGHT))
  {
    PhysicsSetRotationalVelocity(physics, -spaceshipTurnRateMax);
  }
  else
  {
    PhysicsSetRotationalVelocity(physics, 0);
  }
}

void BehaviorPlayerUpdateVelocity(BehaviorPtr behavior, float dt)
{
	Vector2D rotate = { 0 };
  Vector2D velocity = { 0 };
  float speed = 0;
  TransformPtr transform = GameObjectGetTransform(behavior->parent);
  PhysicsPtr physics = GameObjectGetPhysics(behavior->parent);

  if (transform && physics)
  {
	  float rotation = TransformGetRotation(transform);
	  Vector2DFromAngleRad(&rotate, rotation);

    velocity = PhysicsGetVelocity(physics);
    Vector2DScale(&rotate, &rotate, spaceshipAcceleration);
    Vector2DScale(&rotate, &rotate, dt);
    Vector2DAdd(&velocity, &velocity, &rotate);

    speed = Vector2DLength(&velocity);
    if (speed > spaceshipSpeedMax)
    {
      Vector2DScale(&velocity, &velocity, (spaceshipSpeedMax / speed));
    }

    PhysicsVelocity(physics, &velocity);
  }
}

void BehaviorPlayerUpdateWeapon(BehaviorPtr behavior, float dt)
{
  if (behavior->timer > 0)
  {
    behavior->timer -= dt;
    if (behavior->timer < 0)
    {
      behavior->timer = 0;
    }
  }
  if (AEInputCheckCurr(VK_SPACE))
  {
    if (behavior->timer <= 0)
    {
      BehaviorPlayerSpawnBullet(behavior);
      behavior->timer = spaceshipWeaponCooldownTime;
    }
  }
}

void BehaviorPlayerSpawnBullet(BehaviorPtr behavior)
{
  GameObjectPtr bullet = GameObjectManagerGetArchetype("Bullet");

  if (bullet)
  {
    GameObjectPtr clone = GameObjectClone(bullet);
    TransformPtr tClone = GameObjectGetTransform(clone);
    TransformPtr ship = GameObjectGetTransform(behavior->parent);
    float shipRotation = TransformGetRotation(ship);
    Vector2D shipTranslate = *TransformGetTranslation(ship);
    TransformSetTranslation(tClone, &shipTranslate);
    TransformSetRotation(tClone, shipRotation);
    GameObjectSetTransform(clone, tClone);
    Vector2D rotate = { 0 };
    Vector2DFromAngleRad(&rotate, shipRotation);
    PhysicsPtr pClone = GameObjectGetPhysics(clone);
    Vector2D velocity = { 0 };
    Vector2DScale(&velocity, &rotate, spaceshipWeaponBulletSpeed);
    PhysicsVelocity(pClone, &velocity);
    GameObjectSetPhysics(clone, pClone);

    GameObjectManagerAdd(clone);
  }
}