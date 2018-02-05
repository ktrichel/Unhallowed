//------------------------------------------------------------------------------
//
// File Name:	GameStateStub.c
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameStateManager.h"
#include "GameStateStub.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Stub game state.
void GameStateStubLoad()
{
	TraceMessage("Stub: Load");
}

// Initialize the memory associated with the Stub game state.
void GameStateStubInit()
{
	TraceMessage("Stub: Init");
}

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateStubUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	TraceMessage("Stub: Update");

	GameStateManagerSetNextState(GsQuit);
}

// Shutdown any memory associated with the Stub game state.
void GameStateStubShutdown()
{
	TraceMessage("Stub: Shutdown");
}

// Unload the resources associated with the Stub game state.
void GameStateStubUnload()
{
	TraceMessage("Stub: Unload");
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

