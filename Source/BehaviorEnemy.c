//------------------------------------------------------------------------------
//
// File Name:	BehaviorEnemy.c
// Author(s):	Kyle Trichel (kyle.trichel)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorEnemy.h"
#include "Behavior.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "BehaviorBullet.h"
#include "GameObjectManager.h"
#include <AEEngine.h>
#include <cstdlib>
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

enum Enemy
{
  cenemyInvalid,
  cenemyIdle,
  cenemyThrust,
  cenemyMove
};

static const float enemyAcceleration = 150.0f;
static const float enemySpeedMax = 500.0f;
static const float enemyTurnRateMax = PI / 1.5f;
static const float enemyWeaponCooldownTime = 0.25f;
static const float enemyWeaponBulletSpeed = 750.0f;


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


static void BehaviorEnemyUpdateRotation(BehaviorPtr behavior, float dt);
static void BehaviorEnemyUpdateVelocity(BehaviorPtr behavior, float dt);
static void BehaviorEnemyUpdateWeapon(BehaviorPtr behavior, float dt);
static void BehaviorEnemySpawnBullet(BehaviorPtr behavior);


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (enemy) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
BehaviorPtr BehaviorEnemyCreate(void)
{
  BehaviorPtr behavior = calloc(1, sizeof(Behavior));
  if (behavior)
  {
    behavior->stateCurr = cenemyInvalid;
    behavior->stateNext = cenemyIdle;
    behavior->onInit = BehaviorEnemyInit;
    behavior->onExit = BehaviorEnemyExit;
    behavior->onUpdate = BehaviorEnemyUpdate;

    return behavior;
  }
  return NULL;
}

// Initialize the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
void BehaviorEnemyInit(BehaviorPtr behavior)
{
  UNREFERENCED_PARAMETER(behavior);
}

// Update the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorEnemyUpdate(BehaviorPtr behavior, float dt)
{
  switch (behavior->stateCurr)
  {
  case cenemyIdle:
    BehaviorEnemyUpdateWeapon(behavior, dt);
    /* if (AEInputCheckTriggered(VK_UP))
    {
    behavior->stateNext = cenemyThrust;
    }*/
    break;
  case cenemyThrust:
    BehaviorEnemyUpdateWeapon(behavior, dt);
    /*if (!AEInputCheckCurr(VK_UP))
    {
    behavior->stateNext = cenemyIdle;
    }*/
    break;
  case cenemyMove:
    BehaviorEnemyUpdatePosition(behavior, dt);
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
void BehaviorEnemyExit(BehaviorPtr behavior)
{
  UNREFERENCED_PARAMETER(behavior);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void BehaviorEnemyUpdateWeapon(BehaviorPtr behavior, float dt)
{
  if (behavior->timer > 0)
  {
    behavior->timer -= dt;
    if (behavior->timer < 0)
    {
      behavior->timer = 0;
    }
  }

  if (behavior->timer <= 0)
  {
    BehaviorEnemySpawnBullet(behavior);
    behavior->timer = enemyWeaponCooldownTime;
  }
}

void BehaviorEnemyUpdatePosition(BehaviorPtr behavior, float dt)
{
  float timer = (float)(rand() % 10);
    if (timer > 0)
    {
      timer -= dt;
      if (timer < 0)
      {
        timer = 0;
      }
    }
    if (timer <= 0)
    {
      PhysicsPtr enemyPhysics = PhysicsCreate();
      Vector2D enemyVelocityX = { 0 };
      int posNeg = rand() % 10;
      if (posNeg < 5)
      {
        Vector2D enemyVelocityX = { (float)(rand() % 10), 0 };
      }
      else if (posNeg >= 5)
      {
        Vector2D enemyVelocityX = { -(float)(rand() % 10), 0 };
      }
      PhysicsVelocity(enemyPhysics, &enemyVelocityX);
      GameObjectSetPhysics(behavior->parent, enemyPhysics);
    }
}

void BehaviorEnemySpawnBullet(BehaviorPtr behavior)
{
  GameObjectPtr bullet = GameObjectManagerGetArchetype("Bullet");
  
  Vector2D Player;
  Vector2D Normal;

  if (bullet)
  {
    
    GameObjectPtr clone = GameObjectClone(bullet);
    TransformPtr tClone = GameObjectGetTransform(clone);
    TransformPtr enemy = GameObjectGetTransform(behavior->parent);
    float enemyRotation = TransformGetRotation(enemy);
    Vector2D enemyTranslate = *TransformGetTranslation(enemy);
    Vector2DSet(&Player, (float)(rand()%100), (float)(rand()%100));
    Vector2DSub(&Normal, &Player, &enemyTranslate);
    Vector2DNormalize(&Normal, &Normal);
    float angle = atan2f(Normal.y, Normal.x);
    Vector2DScale(&Normal, &Normal, enemyWeaponBulletSpeed);
    TransformSetTranslation(tClone, &enemyTranslate);
    TransformSetRotation(tClone, angle);
    GameObjectSetTransform(clone, tClone);
    Vector2D rotate = { 0 };
    Vector2DFromAngleRad(&rotate, enemyRotation);
    PhysicsPtr pClone = GameObjectGetPhysics(clone);
    Vector2D velocity = { 0 };
    Vector2DScale(&velocity, &rotate, enemyWeaponBulletSpeed);
    PhysicsVelocity(pClone, &Normal);
    GameObjectSetPhysics(clone, pClone);

    GameObjectManagerAdd(clone);
  }
 
}