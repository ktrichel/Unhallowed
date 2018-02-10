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
#include "Sprite.h"
#include "SpriteSource.h"
#include "AnimationSequence.h"
#include "Physics.h"
#include "Collision.h"
#include <AEEngine.h>
#include <stdlib.h>

static int numLives = 0;

static AEGfxTexture * pTexture;
static AEGfxVertexList * pMesh;
static SpritePtr pSprite;
static SpriteSourcePtr pSSource;
static AEGfxTexture * pTexture2;
static AEGfxVertexList * pMesh2;
static SpritePtr pSprite2;
static SpriteSourcePtr pSSource2;
static AnimationPtr pAnimation;
static AEVec2 Position;

static TransformPtr objTransform;
static PhysicsPtr objPhysics;
static BoundingBoxPtr BoxEarth;
static BoundingBoxPtr BoxNumber;

static AEVec2 Empty = { 0 };
static AEVec2 Earth = { 0.0f, -500.0f };
static AEVec2 Velocity = { 0.0f, 0.0f };
static AEVec2 Acceleration = { 0.0f, -20.0f };
static AEVec2 NumberHalfSize = { 50.0f, 50.0f };
static AEVec2 EarthHalfSize = { 300.0f, 300.0f };
static bool IsJumping = 0;

void GameStateLevel1Load()
{
	TraceMessage("Level1: Load");

	FILE *Level1file;

	fopen_s(&Level1file, "Data/Level1_Lives.txt", "rt");

	if (Level1file)
	{
		fscanf_s(Level1file, "%d", &numLives);
		Position.x = 0;
		Position.y = 0;
		pMesh = MeshCreateQuad(50, 50, 0.25, 0.25, "Mesh4x4");
		pMesh2 = MeshCreateQuad(300, 300, 1, 1, "Mesh1x1");
		pTexture = AEGfxTextureLoad("Assets\\Hexidecimal.png");
		pTexture2 = AEGfxTextureLoad("Assets\\PlanetTexture.png");
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
	pSSource2 = SpriteSourceCreate(1, 1, pTexture2);
	pSprite = SpriteCreate("Level1 Sprite");
	pSprite2 = SpriteCreate("second Level1 Sprite");
	SpriteSetMesh(pSprite, pMesh);
	SpriteSetMesh(pSprite2, pMesh2);
	SpriteSetSpriteSource(pSprite, pSSource);
	SpriteSetSpriteSource(pSprite2, pSSource2);
	SpriteSetFrame(pSprite, 0);
	pAnimation = AnimationCreate(pSprite);
	AnimationPlay(pAnimation, 3, 0.25f, true);
	
	//Set Alpha Engine BG to white(1,1,1)
	AEGfxSetBackgroundColor(1, 1, 1);
	//Set AEG blend mode to blend
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	objPhysics = CreatePhysics(Empty, Acceleration, Velocity, 0.0f );
	objTransform = CreateTransform();
	BoxNumber = CreateBoundingBox(Empty, NumberHalfSize);
	BoxEarth = CreateBoundingBox(Earth, EarthHalfSize);
}

void GameStateLevel1Update(float dt)
{
	TraceMessage("Level1: Update");
	if (AEInputCheckCurr(VK_RIGHT) && 
		(GetOldTranslation(objPhysics).x + NumberHalfSize.x - 5.0f<= Earth.x - EarthHalfSize.x || 
		 GetOldTranslation(objPhysics).y - NumberHalfSize.y + 5.0f>= Earth.y + EarthHalfSize.y))
	{
		TransformVelocity(objTransform, 3.0f, 0.0f);
		AnimationUpdate(pAnimation, dt);
	}
	if (AEInputCheckCurr(VK_LEFT) && 
		(GetOldTranslation(objPhysics).x - NumberHalfSize.x + 5.0f>= Earth.x + EarthHalfSize.x ||
		 GetOldTranslation(objPhysics).y - NumberHalfSize.y + 5.0f>= Earth.y + EarthHalfSize.y))
	{
		TransformVelocity(objTransform, -3.0f, 0.0f);
		AnimationUpdate(pAnimation, dt);
	}
	if (CollisionCheckTop(BoxNumber, BoxEarth) == 1)
	{
		IsJumping = 0;
		PhysicsAcceleration(objPhysics, 0.0f, 0.0f);
		PhysicsVelocity(objPhysics, 0.0f, 0.0f);

		//accidental implementation of wall climbing?
		if (AEInputCheckCurr(VK_UP))
		{
			AnimationUpdate(pAnimation, dt);
			IsJumping = 1;
			PhysicsAcceleration(objPhysics, 0.0f, -300.0f);
			PhysicsVelocity(objPhysics, 0.0f, 200.0f);
			//TransformVelocity(objTransform, 0.0f, 3.0f);
		}

    /*
    if (AEInputCheckCurr(VK_DOWN))
    {
      AnimationUpdate(pAnimation, dt);
      PhysicsAcceleration(objPhysics, 0.0f, 300.0f);
      PhysicsVelocity(objPhysics, 0.0f, -200.0f);
    }
    */
	}
	else if(IsJumping == 0)
	{
		PhysicsAcceleration(objPhysics, 0.0f, -80.0f);
	}
  if (GetOldTranslation(objPhysics).y < -800.0f)
  {
    SetTranslation(objTransform, 0.0f, 0.0f);
    SetPhysicsTranslation(objPhysics, 0.0f, 0.0f);
  }


	AEGfxSetCamPosition(GetOldTranslation(objPhysics).x, GetOldTranslation(objPhysics).y);
	UpdateBoundingBox(BoxNumber, GetOldTranslation(objPhysics));
	PhysicsUpdate(objPhysics, objTransform, dt);
	SpriteDraw(pSprite2, Earth);
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
  FreeBoundingBox(&BoxNumber);
  FreeBoundingBox(&BoxEarth);
  SpriteFree(&pSprite2);
  SpriteSourceFree(&pSSource2);
}

void GameStateLevel1Unload()
{
	TraceMessage("Level1: Unload");
	AEGfxTextureUnload(pTexture);
	AEGfxMeshFree(pMesh);
  AEGfxTextureUnload(pTexture2);
  AEGfxMeshFree(pMesh2);
}
