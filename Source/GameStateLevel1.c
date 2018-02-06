//------------------------------------------------------------------------------
//
// File Name:	GameStateLevel1.c
// Author(s):	Mubarak Al-Sabah
// Project:		MyGame
// Course:		CS230S18
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameStateManager.h"
#include "GameStateLevel1.h"
#include "Trace.h"
#include "Mesh.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include "AnimationSequence.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Physics.h"
#include <AEEngine.h>
#include <stdlib.h>

static int numLives = 0;

static AEGfxTexture * pTexture;
static AEGfxVertexList * pMesh;
static SpritePtr pSprite;
static SpriteSourcePtr pSSource;
static AnimationPtr pAnimation;
static AEVec2 Position;

static TransformPtr objTransform;
static PhysicsPtr objPhysics;

static AEVec2 Empty = { 0.0f };
static AEVec2 GravityAcceleration = { 0.0f, -9.81f };
static AEVec2 PlayerVelocity = { 3.0f, 3.0f };

void GameStateLevel1Load()
{
	TraceMessage("Level1: Load");

	FILE *Level1file;
	char buffer[16] = { 0 };

	fopen_s(&Level1file, "Data/Level1_Lives.txt", "rt");

	if (Level1file)
	{
		fgets(buffer, 16, Level1file);
		numLives = atoi(buffer);
		Position.x = 0;
		Position.y = 0;
		pMesh = MeshCreateQuad(50, 50, 0.25, 0.25, "Mesh4x4");
		pTexture = AEGfxTextureLoad("Assets\\Hexidecimal.png");
		fclose(Level1file);
	}
	else
	{
		TraceMessage("Failed to Load Level1_Lives.txt\n");
	}
}

void GameStateLevel1Init()
{
	TraceMessage("Level1: Init");
	pSSource = SpriteSourceCreate(4, 4, pTexture);
	pSprite = SpriteCreate("Level1 Sprite");
	SpriteSetMesh(pSprite, pMesh);
	SpriteSetSpriteSource(pSprite, pSSource);
	SpriteSetFrame(pSprite, 0);
	pAnimation = AnimationCreate(pSprite);
	AnimationPlay(pAnimation, 3, 0.25f, true);
	
	//Set Alpha Engine BG to white(1,1,1)
	AEGfxSetBackgroundColor(1, 1, 1);
	//Set AEG blend mode to blend
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	objPhysics = CreatePhysics(Empty, GravityAcceleration, Empty, 0.0f );
	objTransform = CreateTransform();
}

void GameStateLevel1Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	TraceMessage("Level1: Update");
	if (AEInputCheckCurr(VK_RIGHT))
	{
		TransformVelocity(objTransform, PlayerVelocity.x, 0.0f);
		AnimationUpdate(pAnimation, dt);
	}
	if (AEInputCheckCurr(VK_LEFT))
		TransformVelocity(objTransform, -PlayerVelocity.x, 0.0f);
	if (AEInputCheckCurr(VK_UP))
		TransformVelocity(objTransform, 0.0f, PlayerVelocity.y);

	PhysicsUpdate(objPhysics, objTransform, dt);
	SpriteDraw(pSprite, GetOldTranslation(objPhysics));
}

void GameStateLevel1Shutdown()
{
	TraceMessage("Level1: Shutdown");
	FreeTransform(&objTransform);
	FreePhysics(&objPhysics);
	AnimationFree(&pAnimation);
	SpriteFree(&pSprite);
	SpriteSourceFree(&pSSource);
}

void GameStateLevel1Unload()
{
	TraceMessage("Level1: Unload");
	AEGfxTextureUnload(pTexture);
	AEGfxMeshFree(pMesh);
	
}
