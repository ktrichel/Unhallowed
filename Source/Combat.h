//------------------------------------------------------------------------------
//
// File Name:	Combat.h
// Author(s):	Drake Mathis (login ID)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------
typedef struct Combat * CombatPtr;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
CombatPtr CombatCreate(void);

void CombatFree(CombatPtr combat);

void CombatUpdate(CombatPtr enemyAttacks, CombatPtr playerAttacks, GameObjectPtr enemies, GameObjectPtr character);

void EnemyResolution(GameObjectPtr enemies, CombatPtr playerAttack, int length);

void PlayerResolution(GameObjectPtr character, CombatPtr enemyAttacks);

void DisplaceObjectRight(GameObjectPtr gameObject);

void DisplaceObjectLeft(GameObjectPtr gameObject);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif



/*
	projectile :			check collision and destroy on collision
							health reduction
							knockback (if projectile hits target move target away from collision)

	
	Hitbox :				struct(?)
							TransformPtr (Rotatation) (knockback)
							Damage
							SpritePtr

	Damage Resolution :		
*/