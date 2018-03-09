//------------------------------------------------------------------------------
//
// File Name:	GameStateGameWin.h
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

// Load the resources associated with the GameWin game state.
void GameStateGameWinLoad();

// Initialize the memory associated with the GameWin game state.
void GameStateGameWinInit();

// Update the GameWin game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateGameWinUpdate(float dt);

// Shutdown any memory associated with the GameWin game state.
void GameStateGameWinShutdown();

// Unload the resources associated with the GameWin game state.
void GameStateGameWinUnload();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

