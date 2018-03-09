#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Animation.h"
#include "Physics.h"
#include "Collision.h"
#include "Sprite.h"
#include "Behavior.h"

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct GameObject * GameObjectPtr;

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

// Dynamically allocate a new game object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Params:
//	 name = The name of the game object being created.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
GameObjectPtr GameObjectCreate(const char * name);

// Dynamically allocate a clone of an existing game object.
// Params:
//	 other = Pointer to the game object to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned object,
//	   else return NULL.
GameObjectPtr GameObjectClone(const GameObjectPtr other);

// Free the memory associated with a game object.
// (Also, set the game object pointer to NULL.)
// Params:
//	 gameObject = Pointer to the game object.
void GameObjectFree(GameObjectPtr * gameObject);

// Flag a game object for destruction.
// (Note: This is to avoid game objects being destroyed while they are being processed.)
// Params:
//	 gameObject = Pointer to the game object to be destroyed.
// Returns:
//	 If 'gameObject' is valid,
//	   then set the 'isDestroyed' boolean variable,
//	   else bail.
void GameObjectDestroy(GameObjectPtr gameObject);

// Check whether a game object has been flagged for destruction.
// Params:
//	 gameObject = Pointer to the game object to be checked.
// Returns:
//	 If 'gameObject' is valid,
//	   then return the 'isDestroyed' boolean variable,
//	   else return false.
bool GameObjectIsDestroyed(GameObjectPtr gameObject);

// Attach an animation component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   animation = Pointer to the animation component to be attached.
void GameObjectSetAnimation(GameObjectPtr gameObject, AnimationPtr animation);

// Attach a behavior component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   behavior = Pointer to the behavior component to be attached.
void GameObjectSetBehavior(GameObjectPtr gameObject, BehaviorPtr behavior);

// Attach a physics component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   physics = Pointer to the physics component to be attached.
void GameObjectSetPhysics(GameObjectPtr gameObject, PhysicsPtr physics);

// Attach a sprite component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   sprite = Pointer to the sprite component to be attached.
void GameObjectSetSprite(GameObjectPtr gameObject, SpritePtr sprite);

// Attach a transform component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   transform = Pointer to the transform component to be attached.
void GameObjectSetTransform(GameObjectPtr gameObject, TransformPtr transform);

// Get the game object's name.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the game object's name,
//		else return NULL.
const char * GameObjectGetName(const GameObjectPtr gameObject);

// Compare the game object's name with the specified name.
// Params:
//	 gameObject = Pointer to the game object.
//   name = Pointer to the name to be checked.
// Returns:
//	 If the game object pointer is valid,
//		then return true if the names match, false otherwise,
//		else return false.
bool GameObjectIsNamed(const GameObjectPtr gameObject, const char * name);

// Get the animation component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached animation component,
//		else return NULL.
AnimationPtr GameObjectGetAnimation(const GameObjectPtr gameObject);

// Get the behavior component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached behavior component,
//		else return NULL.
BehaviorPtr GameObjectGetBehavior(const GameObjectPtr gameObject);

// Get the physics component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached physics component,
//		else return NULL.
PhysicsPtr GameObjectGetPhysics(const GameObjectPtr gameObject);

// Get the sprite component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached sprite component,
//		else return NULL.
SpritePtr GameObjectGetSprite(const GameObjectPtr gameObject);

// Get the transform component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached transform component,
//		else return NULL.
TransformPtr GameObjectGetTransform(const GameObjectPtr gameObject);

// Update any components attached to the game object.
// (Hint: You will need to call AnimationUpdate() and PhysicsUpdate().)
// (NOTE: You must first check for valid pointers before calling these functions.)
// Params:
//	 gameObject = Pointer to the game object.
//	 dt = Change in time (in seconds) since the last game loop.
void GameObjectUpdate(GameObjectPtr gameObject, float dt);

// Draw any visible components attached to the game object.
// (Hint: You will need to call SpriteDraw(), passing the sprite and transform components.)
// (NOTE: You must first check for valid pointers before calling this function.)
// Params:
//	 gameObject = Pointer to the game object.
void GameObjectDraw(GameObjectPtr gameObject);

void GameObjectSetHealth(GameObjectPtr gameObject, int health);

int GameObjectGetHealth(GameObjectPtr gameObject);

void GameObjectSetBoundingBox(GameObjectPtr gameObject, BoundingBoxPtr box);

BoundingBoxPtr GameObjectGetBoundingBox(GameObjectPtr gameObject);

GameObjectPtr GameObjectCreateTile(Vector2D scale, Vector2D position, AEGfxVertexList * mesh, SpriteSourcePtr sSource, Vector2D halfsize);

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif