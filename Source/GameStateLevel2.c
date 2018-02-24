//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel2.c
// Author(s):	Mubarak Al-Sabah
// Project:		MyGame
// Course:		CS230S18
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameStateManager.h"
#include "GameStateLevel2.h"
#include "Trace.h"
#include "Mesh.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include "AnimationSequence.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include <AEEngine.h>
#include <stdlib.h>

static int numLives = 0;

static AEGfxTexture * pTexture;
static AEGfxVertexList * pMesh;
static SpritePtr pSprite;
static SpriteSourcePtr pSSource;
static AnimationPtr pAnimation;
static AnimationSequencePtr pASequence;
static AnimationFrame AArray[3] = { {4, 0.32f},{2, 0.32f},{5, 0.5f} };
static AEVec2 Position;

void GameStateLevel2Load()
{
	TraceMessage("Level2: Load");

	FILE *Level2Lives;
	char buffer[16] = { 0 };

	fopen_s(&Level2Lives, "Data/Level2_Lives.txt", "rt");
	if (Level2Lives)
	{
		fgets(buffer, 16, Level2Lives);
		numLives = atoi(buffer);
		Position.x = 0;
		Position.y = 0;
		pMesh = MeshCreateQuad(300, 300, 0.25, 0.25, "Mesh4x4");
		pTexture = AEGfxTextureLoad("Assets\\Hexidecimal.png");
		fclose(Level2Lives);
	}
	else
	{
		TraceMessage("Failed to Load Level2_Lives.txt");
	}
}

void GameStateLevel2Init()
{
	TraceMessage("Level2: Init");

	pSSource = SpriteSourceCreate(4, 4, pTexture);
	pSprite = SpriteCreate("Level2 Sprite");
	SpriteSetMesh(pSprite, pMesh);
	SpriteSetSpriteSource(pSprite, pSSource);
	pAnimation = AnimationCreate(pSprite);
	
	//creating a non looping animation using animation frame array?
	pASequence = AnimationSequenceCreate(_countof(AArray), AArray, 0);
	AnimationPlaySequence(pAnimation, pASequence);

	//Set Alpha Engine BG to white(1,1,1)
	AEGfxSetBackgroundColor(1, 1, 1);
	//Set AEG blend mode to blend
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

void GameStateLevel2Update(float dt)
{
	TraceMessage("Level2: Update");

	AnimationUpdate(pAnimation, dt);
	SpriteDraw(pSprite, Position);

	if (AnimationIsDone(pAnimation))
	{
		numLives -= 1;

		if (numLives == 1)
			AnimationPlaySequence(pAnimation, pASequence);
	}

	if (numLives == 0)
		GameStateManagerSetNextState(GsQuit);
}


void GameStateLevel2Shutdown()
{
	TraceMessage("Level2: Shutdown");
	SpriteFree(&pSprite);
	SpriteSourceFree(&pSSource);
	AnimationFree(&pAnimation);
	AnimationSequenceFree(&pASequence);
}

void GameStateLevel2Unload()
{
	TraceMessage("Level2: Unload");
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTexture);
}

void SetCam()
{

  AEGfxSetCamPosition(1, 1);
}