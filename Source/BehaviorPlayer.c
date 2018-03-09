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

enum Player
{
  cSpaceplayerInvalid,
  cSpaceplayerIdle,
  cSpaceplayerThrust
};

static const float playerAcceleration = 150.0f;
static const float playerSpeedMax = 500.0f;
static const float playerTurnRateMax = PI / 1.5f;
static const float playerWeaponCooldownTime = 0.25f;
static const float playerWeaponBulletSpeed = 750.0f;


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

// Dynamically allocate a new (Spaceplayer) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
BehaviorPtr BehaviorPlayerCreate(void)
{
  BehaviorPtr behavior = calloc(1, sizeof(Behavior));
  if (behavior)
  {
    behavior->stateCurr = cSpaceplayerInvalid;
    behavior->stateNext = cSpaceplayerIdle;
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
  case cSpaceplayerIdle:
    BehaviorPlayerUpdateWeapon(behavior, dt);
   /* if (AEInputCheckTriggered(VK_UP))
    {
      behavior->stateNext = cSpaceplayerThrust;
    }*/
    break;
  case cSpaceplayerThrust:
    BehaviorPlayerUpdateWeapon(behavior, dt);
    /*if (!AEInputCheckCurr(VK_UP))
    {
      behavior->stateNext = cSpaceplayerIdle;
    }*/
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
  if (AEInputCheckCurr(VK_LBUTTON))
  {
    if (behavior->timer <= 0)
    {
      BehaviorPlayerSpawnBullet(behavior);
      behavior->timer = playerWeaponCooldownTime;
    }
  }
}

void BehaviorPlayerSpawnBullet(BehaviorPtr behavior)
{
  GameObjectPtr bullet = GameObjectManagerGetArchetype("Bullet");

  s32 mouseX;
  s32 mouseY;
  float worldX;
  float worldY;
  Vector2D Mouse;
  Vector2D Normal;

  if (bullet)
  {
    AEInputGetCursorPosition(&mouseX, &mouseY);
    AEGfxConvertScreenCoordinatesToWorld((float)mouseX, (float)mouseY, &worldX, &worldY);

    GameObjectPtr clone = GameObjectClone(bullet);
    TransformPtr tClone = GameObjectGetTransform(clone);
    TransformPtr player = GameObjectGetTransform(behavior->parent);
    float playerRotation = TransformGetRotation(player);
    Vector2D playerTranslate = *TransformGetTranslation(player);
    Vector2DSet(&Mouse, worldX, worldY);
    Vector2DSub(&Normal, &Mouse, &playerTranslate);
    Vector2DNormalize(&Normal, &Normal);
    float angle = atan2f(Normal.y, Normal.x);
    Vector2DScale(&Normal, &Normal, playerWeaponBulletSpeed);
    TransformSetTranslation(tClone, &playerTranslate);
    TransformSetRotation(tClone, angle);
    GameObjectSetTransform(clone, tClone);
    Vector2D rotate = { 0 };
    Vector2DFromAngleRad(&rotate, playerRotation);
    PhysicsPtr pClone = GameObjectGetPhysics(clone);
    Vector2D velocity = { 0 };
    Vector2DScale(&velocity, &rotate, playerWeaponBulletSpeed);
    PhysicsVelocity(pClone, &Normal);
    GameObjectSetPhysics(clone, pClone);

    GameObjectManagerAdd(clone);
  }
}