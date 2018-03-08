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
#include "Vector2D.h"
#include "Matrix2D.h"
#include "GameObjectFactory.h"
#include <AEEngine.h>
#include <stdlib.h>

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

static SpritePtr pSprite3;
static SpriteSourcePtr pSSource3;
static AEGfxTexture * pTexture3;
static AEGfxVertexList * pMesh3;


static TransformPtr objTransform;
static PhysicsPtr objPhysics;
static BoundingBoxPtr BoxEarth;
static BoundingBoxPtr BoxNumber;
static BoundingBoxPtr Test;

static AEVec2 Empty = { 0 };
static AEVec2 EarthPos = { 0.0f, -500.0f };
static AEVec2 Velocity = { 0.0f, 0.0f };
static AEVec2 Acceleration = { 0.0f, 0.0f };
static AEVec2 PlayerHalfSize = { 50.0f, 50.0f };
static AEVec2 EarthHalfSize = { 300.0f, 300.0f };
static AEVec2 ShotHalfSize = { 25.0f,25.0f };
static AEVec2 TestStupid = { 0.0f, -200.0f };
static AEVec2 tileScale = { 0.1f, 0.1f };
static AEVec2 dummy = { 60.0f, -60.0f }; // EarthSize times the scale (in this case it is 0.1)
static bool IsJumping = 0;
static AEVec2 Result = { 0 };
static AEVec2 Distance = { 0 };

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static GameObjectPtr GameStateLevel2CreateCharacter(void);
static GameObjectPtr GameStateLevel2CreateEarth(void);
static GameObjectPtr GameStateLevel2CreateShot(void);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

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



void GameStateLevel1Init()
{
	TraceMessage("Level1: Init");
	int i = 0;
	Vector2DSet(&Distance, EarthHalfSize.x * tileScale.x * 2.0f, 0.0f);
	Character = GameStateLevel2CreateCharacter();

	while(i < 20)
	{
		GameObjectFactoryAdd(GameObjectCreateTile(tileScale, Empty, pMesh2, pSSource2, EarthHalfSize));
		Vector2DAdd(&Empty, &Empty, &Distance);
		++i;
	}
	i = 0;
	Vector2DSet(&Distance, 0.0f, EarthHalfSize.y * tileScale.y * 2.0f);
	while(i < 10)
	{
		GameObjectFactoryAdd(GameObjectCreateTile(tileScale, Empty, pMesh2, pSSource2, EarthHalfSize));
		Vector2DAdd(&Empty, &Empty, &Distance);
		++i;
	}

	i = 0;
	Vector2DSet(&Distance, 0.0f, EarthHalfSize.y * tileScale.y * 2.0f);
	Vector2DSet(&Empty, 0.0f, 0.0f);
	while (i < 10)
	{
		GameObjectFactoryAdd(GameObjectCreateTile(tileScale, Empty, pMesh2, pSSource2, EarthHalfSize));
		Vector2DAdd(&Empty, &Empty, &Distance);
		++i;
	}


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
	AEGfxSetBackgroundColor(0.8f, 0.3f, 0.1f);
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
	AEVec2 velocity = { 0 };
	AEVec2 acceleration = { 0 };
	TraceMessage("Level1: Update");

	GameObjectPtr collidedTile = GameObjectFactoryCollision(Character);

	if (AEInputCheckCurr(0x31))
	{
		GameStateManagerSetNextState(GsRestart);
	}
	if (AEInputCheckCurr(VK_SPACE))
	{
		Shot = GameStateLevel2CreateShot();
		Vector2DSet(&velocity, 500.0f, 0.0f);
		PhysicsVelocity(GameObjectGetPhysics(Shot), velocity);
	}

	if (AEInputCheckCurr(VK_RIGHT) &&  
		CollisionCheckCollidedSide(GameObjectGetBoundingBox(Character), GameObjectGetBoundingBox(collidedTile)) != 1)
	{
		Vector2DSet(&velocity, 3.0f, 0.0f);
		TransformVelocity(GameObjectGetTransform(Character), velocity);
		SetAnimationIsRunning(GameObjectGetAnimation(Character), 1);
	}
	else if (AEInputCheckCurr(VK_LEFT) &&
		CollisionCheckCollidedSide(GameObjectGetBoundingBox(Character), GameObjectGetBoundingBox(collidedTile)) != 3)
	{
		Vector2DSet(&velocity, -3.0f, 0.0f);
		TransformVelocity(GameObjectGetTransform(Character), velocity);
		SetAnimationIsRunning(GameObjectGetAnimation(Character), 1);
	}
	else
	{
		SetAnimationIsRunning(GameObjectGetAnimation(Character), 0);
	}

	if (collidedTile)
	{
		Vector2DSet(&velocity, 0.0f, 0.0f);
		IsJumping = 0;

		Vector2DSet(&acceleration, 0.0f, 0.0f);
		PhysicsAcceleration(GameObjectGetPhysics(Character), acceleration);
		PhysicsVelocity(GameObjectGetPhysics(Character), velocity);
		Result = GetOldTranslation(GameObjectGetPhysics(collidedTile));
		Vector2DAdd(&Result, &Result, &dummy);
		Vector2DNeg(&Result, &Result);
		
		SetPhysicsTranslation(GameObjectGetPhysics(Character), Result);

		if (AEInputCheckCurr(VK_UP))
		{
			Vector2DSet(&velocity, 0.0f, 220.0f);
			Vector2DSet(&acceleration, 0.0f, -300.0f);
			AnimationUpdate(GameObjectGetAnimation(Character), dt);
			IsJumping = 1;
			PhysicsAcceleration(GameObjectGetPhysics(Character), acceleration);
			PhysicsVelocity(GameObjectGetPhysics(Character), velocity);
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
	else if (IsJumping == 0)
	{
		Vector2DSet(&acceleration, 0.0f, -80.0f);
		PhysicsAcceleration(GameObjectGetPhysics(Character), acceleration);
	}
	
	if (GetOldTranslation(GameObjectGetPhysics(Character)).y < -1500.0f)
	{
	 TransformSetTranslation(GameObjectGetTransform(Character), &Empty);
	 SetPhysicsTranslation(GameObjectGetPhysics(Character), Empty);
	}


	PhysicsUpdate(GameObjectGetPhysics(Shot), GameObjectGetTransform(Shot), dt);
	//UpdateBoundingBox(GameObjectGetBoundingBox(Character), GetOldTranslation(GameObjectGetPhysics(Character)));

	GameObjectUpdate(Character, dt);
	GameObjectFactoryUpdate(dt);

	GameObjectDraw(Shot);
	GameObjectDraw(Character);
	GameObjectFactoryDraw();

	AEGfxSetCamPosition(GetOldTranslation(GameObjectGetPhysics(Character)).x, GetOldTranslation(GameObjectGetPhysics(Character)).y);
}

void GameStateLevel1Shutdown()
{
	TraceMessage("Level1: Shutdown");
	GameObjectFactoryFree();
	SpriteSourceFree(&pSSource);
	SpriteSourceFree(&pSSource2);
	SpriteSourceFree(&pSSource3);
	GameObjectFree(&Character);
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


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static GameObjectPtr GameStateLevel2CreateCharacter(void)
{
	const AEVec2 Scale = { 1.0f, 1.0f };
	const AEVec2 playerSpawn = { 300.0f, 300.0f };

	GameObjectPtr gObject = GameObjectCreate("Character");
	GameObjectSetTransform(gObject, CreateTransform());
	TransformSetScale(GameObjectGetTransform(gObject), Scale);
	TransformSetRotation(GameObjectGetTransform(gObject), 0);
	TransformSetTranslation(GameObjectGetTransform(gObject), &playerSpawn);
	SpritePtr CharacterSprite = SpriteCreate("Character Sprite");
	SpriteSetMesh(CharacterSprite, pMesh);
	SpriteSetSpriteSource(CharacterSprite, pSSource);
	GameObjectSetSprite(gObject, CharacterSprite);
	GameObjectSetAnimation(gObject, AnimationCreate(CharacterSprite));
	AnimationPlay(GameObjectGetAnimation(gObject), 3, 0.25, true);
	GameObjectSetPhysics(gObject, PhysicsCreate());
	GameObjectSetBoundingBox(gObject, CreateBoundingBox(Empty, PlayerHalfSize));

	return gObject;

}

static GameObjectPtr GameStateLevel2CreateShot(void)
{
	const AEVec2 Scale = { 1.0f, 1.0f };

	GameObjectPtr gObject = GameObjectCreate("Shot");
	GameObjectSetTransform(gObject, CreateTransform());
	TransformSetScale(GameObjectGetTransform(gObject), Scale);
	TransformSetRotation(GameObjectGetTransform(gObject), 0);
	SpritePtr ShotSprite = SpriteCreate("Shot Sprite");
	SpriteSetMesh(ShotSprite, pMesh3);
	SpriteSetSpriteSource(ShotSprite, pSSource3);
	GameObjectSetSprite(gObject, ShotSprite);
	GameObjectSetPhysics(gObject, PhysicsCreate());
	AEVec2 translation = GetOldTranslation(GameObjectGetPhysics(Character));
	SetPhysicsTranslation(GameObjectGetPhysics(gObject), translation);
	TransformSetTranslation(GameObjectGetTransform(gObject), &translation);
	GameObjectSetBoundingBox(gObject, CreateBoundingBox(Empty, ShotHalfSize));

	return gObject;
}
