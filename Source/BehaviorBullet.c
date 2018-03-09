//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.c
// Author(s):	Kyle Trichel (kyle.trichel)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorBullet.h"
#include "Behavior.h"
#include "GameObject.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

enum Bullet
{
  cBulletInvalid,
  cBulletIdle
};

static const float bulletSpeedMax = 500.0f;
static const float bulletLifeTimeMax = 3.0f;

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
static void BehaviorBulletUpdateLifeTimer(BehaviorPtr behavior, float dt);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (Bullet) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
BehaviorPtr BehaviorBulletCreate(void)
{
  BehaviorPtr behavior = calloc(1, sizeof(Behavior));

  if (behavior)
  {
    behavior->stateCurr = cBulletInvalid;
    behavior->stateNext = cBulletIdle;
    behavior->onInit = BehaviorBulletInit;
    behavior->onExit = BehaviorBulletExit;
    behavior->onUpdate = BehaviorBulletUpdate;
    behavior->timer = bulletLifeTimeMax;

    return behavior;
  }
  return NULL;
}

// Initialize the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
void BehaviorBulletInit(BehaviorPtr behavior)
{
  UNREFERENCED_PARAMETER(behavior);
}

// Update the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorBulletUpdate(BehaviorPtr behavior, float dt)
{
  switch (behavior->stateCurr)
  {
  case cBulletIdle:
    BehaviorBulletUpdateLifeTimer(behavior, dt);
  default:
    break;
  }
}

// Exit the current state of the behavior component.
// (Hint: Refer to the lecture notes on finite state machines (FSM).)
// Params:
//	 behavior = Pointer to the behavior component.
//	 dt = Change in time (in seconds) since the last game loop.
void BehaviorBulletExit(BehaviorPtr behavior)
{
  UNREFERENCED_PARAMETER(behavior);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void BehaviorBulletUpdateLifeTimer(BehaviorPtr behavior, float dt)
{
  if (behavior)
  {
    if (behavior->timer > 0)
    {
      behavior->timer -= dt;
      if (behavior->timer <= 0)
      {
        GameObjectDestroy(behavior->parent);
      }
    }
  }
}
