//------------------------------------------------------------------------------
//
// File Name:	GameStateGameOver.c
// Author(s):	Doug Schilling (dschilling)
// Project:		MyGame
// Course:		CS230S18
//
// Copyright 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameStateManager.h"
#include "GameStateGameOver.h"
#include "AEEngine.h"
#include "Trace.h"
#include "animation.h"
#include "Sprite.h"
#include "Mesh.h"
#include "SpriteSource.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Physics.h"


//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------
static const float monkeyWalkSpeed = 500.0f;
static const float monkeyJumpSpeed = 1000.0f;
static const float groundHeight = 90.0f;

static const Vector2D gravityNormal = { 0.0f, -1500.0f };
static const Vector2D gravityNone = { 0.0f, 0.0f };


//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static GameObjectPtr GOPtr;
static int numLives = 0;
static FILE * file1;
static AEGfxTexture * pTexture;
static AEGfxVertexList * xVerList;
static SpriteSourcePtr SptP0;
static AEVec2 xy;
static TransformPtr trfPt;
static AnimationPtr animation;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static GameObjectPtr GameStateLevel1CreateMonkey(void);
//static void GameStateLevel1MoveMonkey(void);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Load the resources associated with the Level1 game state.
void GameStateGameOverLoad()
{
	TraceMessage("GameOver: Load");

	xVerList = MeshCreateQuad(0.5, 0.5, 1.0f, 1.0f, "Mesh3x3");
	pTexture = AEGfxTextureLoad("Assets\\Game_Over_Screen.png");
	if (pTexture != NULL)
	{
		SptP0 = SpriteSourceCreate(1, 1, pTexture);
	}
}

// Initialize the memory associated with the GameOver game state.
void GameStateGameOverInit()
{
	TraceMessage("GameOver: Init");
	GOPtr = GameStateLevel1CreateMonkey();
	AEGfxSetBackgroundColor(0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetCamPosition(10,90);
}

// Update the Level1 game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
/* Tell the compiler that the 'dt' variable is unused. */
//UNREFERENCED_PARAMETER(dt);
void GameStateGameOverUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	TraceMessage("GameOver: Update");
	//GameStateLevel1MoveMonkey();
	GameObjectUpdate(GOPtr, dt);
	GameObjectDraw(GOPtr);
}

// Shutdown any memory associated with the GameOver game state.
void GameStateGameOverShutdown()
{
	TraceMessage("GameOver: Shutdown");
	
	GameObjectFree(&GOPtr);
}

// Unload the resources associated with the GameOver game state.
void GameStateGameOverUnload()
{
	TraceMessage("GameOver: Unload");

	if (SptP0 != NULL)
	{
		SpriteSourceFree(&SptP0);
	}
	if (xVerList != NULL)
	{
		AEGfxMeshFree(xVerList);
	}
	if (pTexture != NULL)
	{
		AEGfxTextureUnload(pTexture);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static GameObjectPtr GameStateLevel1CreateMonkey(void)
{
	GOPtr = GameObjectCreate("Monkey");
	trfPt = TransformCreate(100, groundHeight);
	Vector2D vec;
	vec.x = 980;
	vec.y = 600;
	

	if (trfPt != NULL)
	{
		TransformSetRotation(trfPt, 0);
		TransformSetScale(trfPt, vec);
		
	}

	struct Sprite* spr;
	spr = SpriteCreate("Monkey Sprite");

	if (spr != NULL)
	{
		if (pTexture != NULL)
		{
			SpriteSetMesh(spr, xVerList);
		}
		else
		{
			TraceMessage("pTexture missing");
		}
		if (SptP0 != NULL)
		{
			SpriteSetSpriteSource(spr, SptP0);
		}
		else
		{
			TraceMessage("SptP0 missing");
		}
	}

	struct Animation* Ani;
	Ani = AnimationCreate(spr);
	AnimationPlay(Ani, 1, 100.0f, true);

	struct Physics* phy;
	phy = PhysicsCreate();

	GameObjectSetTransform(GOPtr, trfPt);
	GameObjectSetSprite(GOPtr, spr);
	GameObjectSetAnimation(GOPtr, Ani);
	GameObjectSetPhysics(GOPtr, phy);

	return GOPtr;
}