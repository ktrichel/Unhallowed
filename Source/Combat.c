//------------------------------------------------------------------------------
//
// File Name:	Combat.c
// Author(s):	Drake Mathis (login ID)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Combat.h"
#include "Collision.h"
#include "Physics.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Vector2D.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Combat
{
	const char * name;

	BoundingBoxPtr box;

	PhysicsPtr physics;

	TransformPtr transform;
	
	SpritePtr sprite;

	int health;
}Combat;

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
CombatPtr CombatCreate(void)
{
	CombatPtr combat = calloc(1, sizeof(Combat));
	if (combat)
	{
		return combat;
	}
	return NULL;
}

void CombatFree(CombatPtr combatObject)
{
	if (&combatObject && combatObject)
	{
		free(&combatObject);
		combatObject = NULL;
	}
}

void DisplaceObjectRight(GameObjectPtr gameObject)
{
	PhysicsPtr physics = GameObjectGetPhysics(gameObject);
	PhysicsVelocity(physics, 200.0f, 200.0f);
	PhysicsAcceleration(physics, 0.0f, -300.0f);
	GameObjectSetPhysics(gameObject, physics);
}

void DisplaceObjectLeft(GameObjectPtr gameObject)
{
	PhysicsPtr physics = GameObjectGetPhysics(gameObject);
	PhysicsVelocity(physics, -200.0f, 200.0f);
	PhysicsAcceleration(physics, 0.0f, -300.0f);
	GameObjectSetPhysics(gameObject, physics);
}

void CombatUpdate(CombatPtr enemyAttacks, CombatPtr playerAttacks, GameObjectPtr enemies, GameObjectPtr character)
{
	if ( enemyAttacks && playerAttacks && enemies && character)
	{
		EnemyResolution(enemies, playerAttacks);
		PlayerResolution(character, enemyAttacks);

	}
}

void EnemyResolution(GameObjectPtr enemies, CombatPtr playerAttack, int length)
{
	if (enemies && playerAttack)
	{
		/* Go through enemy array bounding boxes and check if the player attack's bounding box is colling with it
		   If true on collision check detriment the enemy's health variable										*/
		for (int i = 0; i < length; i++)
		{
			if (CollisionCheckLeft(GameObjectGetBoundingBox(enemies), CombatObjectGetBoundingBox(playerAttack)) == 1)
			{
				DisplaceObjectRight(enemies);
			}
			if (CollisionCheckRight(GameObjectGetBoundingBox(enemies), CombatObjectGetBoundingBox(playerAttack)) == 1)
			{
				DisplaceObjectLeft(enemies);
			}
		}
	}
}

void PlayerResolution(GameObjectPtr character, CombatPtr enemyAttacks)
{

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

