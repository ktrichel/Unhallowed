#include "stdafx.h"
#include "GameObject.h"
#include <AEEngine.h>

typedef struct GameObject
{
	const char * name;

	BoundingBoxPtr box;

	PhysicsPtr physics;

	TransformPtr transform;

	AnimationPtr animation;

	SpritePtr sprite;

	int health;
}GameObject;

// Dynamically allocate a new game object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Params:
//	 name = The name of the game object being created.
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
GameObjectPtr GameObjectCreate(const char * name)
{
	GameObjectPtr gameObject = calloc(1, sizeof(GameObject));

	if (gameObject)
	{
		gameObject->name = name;
		return gameObject;
	}
	return NULL;
}
// Free the memory associated with a game object.
// (Also, set the game object pointer to NULL.)
// Params:
//	 gameObject = Pointer to the game object.
void GameObjectFree(GameObjectPtr * gameObject)
{
	if (gameObject && *gameObject)
	{
		free(*gameObject);
		*gameObject = NULL;
	}
}
// Attach an animation component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   animation = Pointer to the animation component to be attached.
void GameObjectSetAnimation(GameObjectPtr gameObject, AnimationPtr animation)
{
	if (gameObject && animation)
	{
		gameObject->animation = animation;
	}
}
// Attach a physics component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   physics = Pointer to the physics component to be attached.
void GameObjectSetPhysics(GameObjectPtr gameObject, PhysicsPtr physics)
{
	if (gameObject && physics)
	{
		gameObject->physics = physics;
	}
}
// Attach a sprite component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   sprite = Pointer to the sprite component to be attached.
void GameObjectSetSprite(GameObjectPtr gameObject, SpritePtr sprite)
{
	if (gameObject && sprite)
	{
		gameObject->sprite = sprite;
	}
}
// Attach a transform component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   transform = Pointer to the transform component to be attached.
void GameObjectSetTransform(GameObjectPtr gameObject, TransformPtr transform)
{
	if (gameObject && transform)
	{
		gameObject->transform = transform;
	}
}

// Get the animation component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached animation component,
//		else return NULL.
AnimationPtr GameObjectGetAnimation(const GameObjectPtr gameObject)
{
	if (gameObject)
	{
		return gameObject->animation;
	}
	return NULL;
}
// Get the physics component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached physics component,
//		else return NULL.
PhysicsPtr GameObjectGetPhysics(const GameObjectPtr gameObject)
{
	if (gameObject)
	{
		return gameObject->physics;
	}
	return NULL;
}
// Get the sprite component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached sprite component,
//		else return NULL.
SpritePtr GameObjectGetSprite(const GameObjectPtr gameObject)
{
	if (gameObject)
	{
		return gameObject->sprite;
	}
	return NULL;
}
// Get the transform component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached transform component,
//		else return NULL.
TransformPtr GameObjectGetTransform(const GameObjectPtr gameObject)
{
	if (gameObject)
	{
		return gameObject->transform;
	}
	return NULL;
}
// Update any components attached to the game object.
// (Hint: You will need to call AnimationUpdate() and PhysicsUpdate().)
// (NOTE: You must first check for valid pointers before calling these functions.)
// Params:
//	 gameObject = Pointer to the game object.
//	 dt = Change in time (in seconds) since the last game loop.
void GameObjectUpdate(GameObjectPtr gameObject, float dt)
{
	if (gameObject)
	{
		AnimationUpdate(gameObject->animation, dt);
		PhysicsUpdate(gameObject->physics, gameObject->transform, dt);
	}
}
// Draw any visible components attached to the game object.
// (Hint: You will need to call SpriteDraw(), passing the sprite and transform components.)
// (NOTE: You must first check for valid pointers before calling this function.)
// Params:
//	 gameObject = Pointer to the game object.
void GameObjectDraw(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		SpriteDraw(gameObject->sprite, GetOldTranslation(gameObject->physics));
	}
}

void GameObjectSetHealth(GameObjectPtr gameObject, int health)
{
	if (gameObject)
	{
		gameObject->health = health;
	}
}

int GameObjectGetHealth(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		return gameObject->health;
	}
	return 0;
}

void GameObjectSetBoundingBox(GameObjectPtr gameObject, BoundingBoxPtr box)
{
	if (gameObject && box)
	{
		gameObject->box = box;
	}
}

BoundingBoxPtr GameObjectGetBoundingBox(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		return gameObject->box;
	}
	return NULL;
}

