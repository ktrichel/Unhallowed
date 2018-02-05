//------------------------------------------------------------------------------
//
// File Name:	Main.c
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright � 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <windows.h>
#include "Engine.h"
#include "GameStateManager.h"
#include "System.h"

//------------------------------------------------------------------------------
// Main Function:
//------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

	// Change in time (in seconds) since the last game loop.
	// A framerate controller is not required for this assignment.
	float dt = 0.0167f;

	// Store the Windows settings passed in WinMain.
	SystemStoreWindowSettings(instanceH, show);

	// Initialize the game engine.
	EngineInit();

	// MAIN LOOP: Do not exit until instructed to do so by the game state manager (GSM).
	while (GameStateManagerIsRunning())
	{
		// Update the game engine.
		EngineUpdate(dt);
	}

	// Shutdown the game engine.
	EngineShutdown();

	return 0;
}