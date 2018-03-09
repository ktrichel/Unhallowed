//------------------------------------------------------------------------------
//
// File Name:	BehaviorEnemy.h
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S18
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

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

  typedef struct Behavior * BehaviorPtr;

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

  // Dynamically allocate a new (Spaceship) behavior component.
  // (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
  BehaviorPtr BehaviorEnemyCreate(void);

  // Initialize the current state of the behavior component.
  // (Hint: Refer to the lecture notes on finite state machines (FSM).)
  // Params:
  //	 behavior = Pointer to the behavior component.
  void BehaviorEnemyInit(BehaviorPtr behavior);

  // Update the current state of the behavior component.
  // (Hint: Refer to the lecture notes on finite state machines (FSM).)
  // Params:
  //	 behavior = Pointer to the behavior component.
  //	 dt = Change in time (in seconds) since the last game loop.
  void BehaviorEnemyUpdate(BehaviorPtr behavior, float dt);

  // Exit the current state of the behavior component.
  // (Hint: Refer to the lecture notes on finite state machines (FSM).)
  // Params:
  //	 behavior = Pointer to the behavior component.
  //	 dt = Change in time (in seconds) since the last game loop.
  void BehaviorEnemyExit(BehaviorPtr behavior);

  //------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

#pragma once
