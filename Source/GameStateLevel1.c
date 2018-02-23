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
#include "GameObject.h"
#include <AEEngine.h>
#include <stdlib.h>

static AEGfxTexture * pTexture;
static AEGfxVertexList * pMesh;
static SpritePtr pSprite;
static SpriteSourcePtr pSSource;
static AEGfxTexture * pTexture2;
static AEGfxVertexList * pMesh2;
static SpritePtr pSprite2;
static SpriteSourcePtr pSSource2;
static AEGfxTexture * pTexture3;
static AEGfxVertexList * pMesh3;
static SpritePtr pSprite3;
static SpriteSourcePtr pSSource3;
static AnimationPtr pAnimation;
static AEVec2 Position;
static GameObjectPtr Character;
static GameObjectPtr Earth;
static GameObjectPtr Shot;

static TransformPtr objTransform;
static PhysicsPtr objPhysics;
static BoundingBoxPtr BoxEarth;
static BoundingBoxPtr BoxNumber;

static AEVec2 Empty = { 0 };
static AEVec2 EarthPos = { 0.0f, -500.0f };
static AEVec2 Velocity = { 0.0f, 0.0f };
static AEVec2 Acceleration = { 0.0f, -20.0f };
static AEVec2 PlayerHalfSize = { 50.0f, 50.0f };
static AEVec2 EarthHalfSize = { 300.0f, 300.0f };
static AEVec2 ShotHalfSize = { 25.0f,25.0f };
static AEVec2 TestStupid = { 0.0f, -200.0f };
static bool IsJumping = 0;


void GameStateLevel1Load()
{
	TraceMessage("Level1: Load");

	pMesh = MeshCreateQuad(50, 50, 0.25, 0.25, "Mesh4x4");
	pMesh2 = MeshCreateQuad(300, 300, 1, 1, "Mesh1x1");
	pMesh3 = MeshCreateQuad(50, 25, .5, .25, "Mesh1x1");
	pTexture = AEGfxTextureLoad("Assets\\Hexidecimal.png");
	pTexture2 = AEGfxTextureLoad("Assets\\PlanetTexture.png");
	pTexture3 = AEGfxTextureLoad("Assets\\runningcat.png");
	pSSource = SpriteSourceCreate(4, 4, pTexture);
	pSSource2 = SpriteSourceCreate(1, 1, pTexture2);
	pSSource3 = SpriteSourceCreate(1, 1, pTexture3);
}


static GameObjectPtr GameStateLevel2CreateCharacter(void)
{
	const AEVec2 Scale = { 300.0f, 300.0f };

	GameObjectPtr gObject = GameObjectCreate("Character");
	GameObjectSetTransform(gObject, CreateTransform());
	TransformSetScale(GameObjectGetTransform(gObject), Scale);
	TransformSetRotation(GameObjectGetTransform(gObject), 0);
	SpritePtr CharacterSprite = SpriteCreate("Character Sprite");
	SpriteSetMesh(CharacterSprite, pMesh);
	SpriteSetSpriteSource(CharacterSprite, pSSource);
	GameObjectSetSprite(gObject, CharacterSprite);
	GameObjectSetAnimation(gObject, AnimationCreate(CharacterSprite));
	AnimationPlay(GameObjectGetAnimation(gObject), 3, 0.25, true);
	GameObjectSetPhysics(gObject, PhysicsCreate());
	PhysicsAcceleration(GameObjectGetPhysics(gObject), 0.0f, -20.0f);
	PhysicsVelocity(GameObjectGetPhysics(gObject), 0.0f, 0.0f);
	GameObjectSetBoundingBox(gObject, CreateBoundingBox(Empty, PlayerHalfSize));

	return gObject;

}

static GameObjectPtr GameStateLevel2CreateEarth(void)
{
	const AEVec2 Scale = { 300.0f, 300.0f };

	GameObjectPtr gObject = GameObjectCreate("Earth");
	GameObjectSetTransform(gObject, TransformCreate(0, 0));
	TransformSetScale(GameObjectGetTransform(gObject), Scale);
	TransformSetRotation(GameObjectGetTransform(gObject), 0);
	SpritePtr EarthSprite = SpriteCreate("Earth Sprite");
	SpriteSetMesh(EarthSprite, pMesh2);
	SpriteSetSpriteSource(EarthSprite, pSSource2);
	GameObjectSetSprite(gObject, EarthSprite);
	GameObjectSetPhysics(gObject, PhysicsCreate());
	PhysicsAcceleration(GameObjectGetPhysics(gObject), 0.0f, 0.0f);
	PhysicsVelocity(GameObjectGetPhysics(gObject), 0.0f, 0.0f);
	SetPhysicsTranslation(GameObjectGetPhysics(gObject), 0.0f, -500.0f);
	GameObjectSetBoundingBox(gObject, CreateBoundingBox(EarthPos, EarthHalfSize));

	return gObject;

}

static GameObjectPtr GameStateLevel2CreateShot(void)
{
	const AEVec2 Scale = { 300.0f, 300.0f };

	GameObjectPtr gObject = GameObjectCreate("Shot");
	GameObjectSetTransform(gObject, CreateTransform());
	TransformSetScale(GameObjectGetTransform(gObject), Scale);
	TransformSetRotation(GameObjectGetTransform(gObject), 0);
	SpritePtr ShotSprite = SpriteCreate("Shot Sprite");
	SpriteSetMesh(ShotSprite, pMesh3);
	SpriteSetSpriteSource(ShotSprite, pSSource3);
	GameObjectSetSprite(gObject, ShotSprite);
	GameObjectSetPhysics(gObject, PhysicsCreate());
	PhysicsAcceleration(GameObjectGetPhysics(gObject), 0.0f, 0.0f);
	PhysicsVelocity(GameObjectGetPhysics(gObject), 0.0f, 0.0f);
	SetPhysicsTranslation(GameObjectGetPhysics(gObject), GetOldTranslation(GameObjectGetPhysics(Character)).x, GetOldTranslation(GameObjectGetPhysics(Character)).y);
	SetTranslation(GameObjectGetTransform(gObject), GetOldTranslation(GameObjectGetPhysics(gObject)).x, GetOldTranslation(GameObjectGetPhysics(gObject)).y);
	GameObjectSetBoundingBox(gObject, CreateBoundingBox(Empty, ShotHalfSize));

	return gObject;
}

void GameStateLevel1Init()
{
	TraceMessage("Level1: Init");
	
	Character = GameStateLevel2CreateCharacter();
	Earth = GameStateLevel2CreateEarth();


	/*
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
	*/
	
	//Set Alpha Engine BG to white(1,1,1)
	AEGfxSetBackgroundColor(1, 1, 1);
	//Set AEG blend mode to blend
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	/*
	objPhysics = CreatePhysics(Empty, Acceleration, Velocity, 0.0f );
	objTransform = CreateTransform();
	BoxNumber = CreateBoundingBox(Empty, NumberHalfSize);
	BoxEarth = CreateBoundingBox(EarthPos, EarthHalfSize);
	*/
}

void GameStateLevel1Update(float dt)
{
	TraceMessage("Level1: Update");
	if (AEInputCheckCurr(0x31))
	{
		GameStateManagerSetNextState(GsRestart);
	}
	if (AEInputCheckCurr(VK_SPACE))
	{
		Shot = GameStateLevel2CreateShot();
		PhysicsVelocity(GameObjectGetPhysics(Shot), 500.0f, 0.0f);
	}

	if (AEInputCheckCurr(VK_RIGHT) && 
		CollisionCheckLeft(GameObjectGetBoundingBox(Character), GameObjectGetBoundingBox(Earth)) == 0)
	{
		TransformVelocity(GameObjectGetTransform(Character), 3.0f, 0.0f);
		AnimationUpdate(GameObjectGetAnimation(Character), dt);
	}
	if (AEInputCheckCurr(VK_LEFT) && 
		CollisionCheckRight(GameObjectGetBoundingBox(Character), GameObjectGetBoundingBox(Earth)) == 0)
	{
		TransformVelocity(GameObjectGetTransform(Character), -3.0f, 0.0f);
		AnimationUpdate(GameObjectGetAnimation(Character), dt);
	}
	if (CollisionCheckTop(GameObjectGetBoundingBox(Character), GameObjectGetBoundingBox(Earth)) == 1)
	{
		IsJumping = 0;
		PhysicsAcceleration(GameObjectGetPhysics(Character), 0.0f, 0.0f);
		PhysicsVelocity(GameObjectGetPhysics(Character), 0.0f, 0.0f);

		//accidental implementation of wall climbing?
		if (AEInputCheckCurr(VK_UP))
		{
			AnimationUpdate(GameObjectGetAnimation(Character), dt);
			IsJumping = 1;
			PhysicsAcceleration(GameObjectGetPhysics(Character), 0.0f, -300.0f);
			PhysicsVelocity(GameObjectGetPhysics(Character), 0.0f, 200.0f);
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
		PhysicsAcceleration(GameObjectGetPhysics(Character), 0.0f, -80.0f);
	}

	 if (GetOldTranslation(GameObjectGetPhysics(Character)).y < -1500.0f)
	{
	 SetTranslation(GameObjectGetTransform(Character), 0.0f, 0.0f);
	 SetPhysicsTranslation(GameObjectGetPhysics(Character), 0.0f, 0.0f);
	}


	PhysicsUpdate(GameObjectGetPhysics(Shot), GameObjectGetTransform(Shot), dt);
	AEGfxSetCamPosition(GetOldTranslation(GameObjectGetPhysics(Character)).x, GetOldTranslation(GameObjectGetPhysics(Character)).y);
	UpdateBoundingBox(GameObjectGetBoundingBox(Character), GetOldTranslation(GameObjectGetPhysics(Character)));
	PhysicsUpdate(GameObjectGetPhysics(Character), GameObjectGetTransform(Character), dt);
	GameObjectDraw(Earth);
	GameObjectDraw(Shot);
	GameObjectDraw(Character);
}

void GameStateLevel1Shutdown()
{
	TraceMessage("Level1: Shutdown");
	SpriteSourceFree(&pSSource);
	SpriteSourceFree(&pSSource2);
	SpriteSourceFree(&pSSource3);
	GameObjectFree(&Character);
	GameObjectFree(&Earth);
	GameObjectFree(&Shot);
}

void GameStateLevel1Unload()
{
	TraceMessage("Level1: Unload");
	AEGfxTextureUnload(pTexture);
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTexture2);
	AEGfxMeshFree(pMesh2);
	AEGfxTextureUnload(pTexture3);
	AEGfxMeshFree(pMesh3);
}
