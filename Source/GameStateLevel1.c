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
#include "Behavior.h"
#include "BehaviorBullet.h"
#include "GameObjectManager.h"
#include "BehaviorPlayer.h"
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
static Vector2D Position;
static GameObjectPtr Character;
static GameObjectPtr Earth;

static AEGfxVertexList*	pMeshBullet = NULL;

static AEGfxVertexList* bgMesh;
static AEGfxTexture* bgTexture;
static SpriteSourcePtr bgSSource;
static SpritePtr bgSprite;
static TransformPtr bgTransform;
static GameObjectPtr background;

static TransformPtr objTransform;
static PhysicsPtr objPhysics;
static BoundingBoxPtr BoxEarth;
static BoundingBoxPtr BoxNumber;
static BoundingBoxPtr Test;

static Vector2D Empty = { 0 };
static Vector2D EarthPos = { 300.0f, 300.0f };
static Vector2D Velocity = { 0.0f, 0.0f };
static Vector2D Acceleration = { 0.0f, 0.0f };
static Vector2D PlayerHalfSize = { 50.0f, 50.0f };
static Vector2D EarthHalfSize = { 300.0f, 300.0f };
static Vector2D TestStupid = { 0.0f, -200.0f };
static Vector2D tileScale = { 0.1f, 0.1f };
static Vector2D dummy = { 60.0f, -60.0f }; // EarthSize times the scale (in this case it is 0.1)
static bool IsJumping = 0;
static Vector2D Result = { 0 };
static Vector2D Distance = { 0 };
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static GameObjectPtr GameStateLevel2CreateCharacter(void);
static GameObjectPtr GameStateLevel2CreateEarth(void);
static void GameStateAsteroidsCreateBulletArchetype(void);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void GameStateLevel1Load()
{
	TraceMessage("Level1: Load");

	pMesh = MeshCreateQuad(50, 50, 0.5, 0.5, "Mesh4x4");
	pMesh2 = MeshCreateQuad(300, 300, 1, 1, "Mesh1x1");
	pMeshBullet = MeshCreateQuad(25, 25, 1, 1, "Mesh1x1");
  bgMesh = MeshCreateQuad(1000, 1000, 1, 1, "Mesh1x1");
	pTexture = AEGfxTextureLoad("Assets\\Knight.png");
	pTexture2 = AEGfxTextureLoad("Assets\\Brick.png");
	pTexture3 = AEGfxTextureLoad("Assets\\Bullet.png");
  bgTexture = AEGfxTextureLoad("Assets\\PlanetTexture.png");
	pSSource = SpriteSourceCreate(2, 2, pTexture);
	pSSource2 = SpriteSourceCreate(1, 1, pTexture2);
	pSSource3 = SpriteSourceCreate(1, 1, pTexture3);
  bgSSource = SpriteSourceCreate(1, 1, bgTexture);
}

void GameStateLevel1Init()
{
	TraceMessage("Level1: Init");

  background = GameObjectCreate("BG");
  bgTransform = CreateTransform();
  TransformSetRotation(bgTransform, 0);
  TransformSetScale(bgTransform, EarthPos);
  bgSprite = SpriteCreate("BG");
  SpriteSetMesh(bgSprite, bgMesh);
  SpriteSetSpriteSource(bgSprite, bgSSource);
  GameObjectSetTransform(background, bgTransform);
  GameObjectSetSprite(background, bgSprite);

  GameStateAsteroidsCreateBulletArchetype();

  Vector2DSet(&Empty, 0.0f, 0.0f);
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
  AEGfxSetBackgroundColor(0.3f, 0.3f, 0.1f);

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
	Vector2D velocity = { 0 };
	Vector2D acceleration = { 0 };
	TraceMessage("Level1: Update");

	GameObjectPtr collidedTile = GameObjectFactoryCollision(Character);

	if (AEInputCheckCurr(0x31))
	{
		GameStateManagerSetNextState(GsRestart);
	}

	if (AEInputCheckCurr('D') &&  
		CollisionCheckCollidedSide(GameObjectGetBoundingBox(Character), GameObjectGetBoundingBox(collidedTile)) != 1)
	{
		Vector2DSet(&velocity, 5.0f, 0.0f);
		TransformVelocity(GameObjectGetTransform(Character), velocity);
		SetAnimationIsRunning(GameObjectGetAnimation(Character), 1);
	}
	else if (AEInputCheckCurr('A') &&
		CollisionCheckCollidedSide(GameObjectGetBoundingBox(Character), GameObjectGetBoundingBox(collidedTile)) != 3)
	{
		Vector2DSet(&velocity, -5.0f, 0.0f);
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
		PhysicsVelocity(GameObjectGetPhysics(Character), &velocity);
		Result = GetOldTranslation(GameObjectGetPhysics(collidedTile));
		Vector2DAdd(&Result, &Result, &dummy);
		Vector2DNeg(&Result, &Result);
		
		SetPhysicsTranslation(GameObjectGetPhysics(Character), Result);

		if (AEInputCheckCurr('W'))
		{
			Vector2DSet(&velocity, 0.0f, 220.0f);
			Vector2DSet(&acceleration, 0.0f, -300.0f);
			AnimationUpdate(GameObjectGetAnimation(Character), dt);
			IsJumping = 1;
			PhysicsAcceleration(GameObjectGetPhysics(Character), acceleration);
			PhysicsVelocity(GameObjectGetPhysics(Character), &velocity);
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


	//UpdateBoundingBox(GameObjectGetBoundingBox(Character), GetOldTranslation(GameObjectGetPhysics(Character)));

	GameObjectUpdate(Character, dt);
	GameObjectFactoryUpdate(dt);

  
	GameObjectDraw(Character);
	GameObjectFactoryDraw();
  GameObjectDraw(background);

	AEGfxSetCamPosition(GetOldTranslation(GameObjectGetPhysics(Character)).x, GetOldTranslation(GameObjectGetPhysics(Character)).y);
}

void GameStateLevel1Shutdown()
{
	TraceMessage("Level1: Shutdown");
  GameObjectManagerShutdown();
	GameObjectFactoryFree();
	SpriteSourceFree(&pSSource);
	SpriteSourceFree(&pSSource2);
	SpriteSourceFree(&pSSource3);
  SpriteSourceFree(&bgSSource);
	GameObjectFree(&Character);
  GameObjectFree(&background);
}

void GameStateLevel1Unload()
{
	TraceMessage("Level1: Unload");
	AEGfxTextureUnload(pTexture);
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTexture2);
	AEGfxMeshFree(pMesh2);
	AEGfxTextureUnload(pTexture3);
  AEGfxMeshFree(pMeshBullet);
  AEGfxTextureUnload(bgTexture);
  AEGfxMeshFree(bgMesh);
}



//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static GameObjectPtr GameStateLevel2CreateCharacter(void)
{
	const Vector2D Scale = { 1.0f, 1.0f };
	const Vector2D playerSpawn = { 100.0f, 100.0f };

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
	AnimationPlay(GameObjectGetAnimation(gObject), 3, 0.1f, true);
	GameObjectSetPhysics(gObject, PhysicsCreate());
	GameObjectSetBoundingBox(gObject, CreateBoundingBox(Empty, PlayerHalfSize));
  GameObjectSetBehavior(gObject, BehaviorPlayerCreate());

	return gObject;

}

static void GameStateAsteroidsCreateBulletArchetype(void)
{
  Vector2D scale = { 1, 1 };
  GameObjectPtr bullet = GameObjectCreate("Bullet");
  TransformPtr trBullet = TransformCreate(0, 0);
  SpritePtr sprBullet = SpriteCreate("Bullet Sprite");
  PhysicsPtr phyByllet = PhysicsCreate();
  BehaviorPtr bBullet = BehaviorBulletCreate();

  TransformSetRotation(trBullet, 0);
  TransformSetScale(trBullet, scale);

  SpriteSetSpriteSource(sprBullet, pSSource3);
  SpriteSetMesh(sprBullet, pMeshBullet);

  GameObjectSetTransform(bullet, trBullet);
  GameObjectSetSprite(bullet, sprBullet);
  GameObjectSetPhysics(bullet, phyByllet);
  GameObjectSetBehavior(bullet, bBullet);

  GameObjectManagerAddArchetype(bullet);
}