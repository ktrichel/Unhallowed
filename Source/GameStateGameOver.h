//------------------------------------------------------------------------------
//
// File Name:	GameStateGameOver.h
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
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

// Load the resources associated with the GameOver game state.
void GameStateGameOverLoad();

// Initialize the memory associated with the GameOver game state.
void GameStateGameOverInit();

// Update the GameOver game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateGameOverUpdate(float dt);

// Shutdown any memory associated with the GameOver game state.
void GameStateGameOverShutdown();

// Unload the resources associated with the GameOver game state.
void GameStateGameOverUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

