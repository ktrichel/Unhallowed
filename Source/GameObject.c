#include "stdafx.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Behavior.h"
#include <AEEngine.h>

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct GameObject
{
	const char * name;

  bool isDestroyed;

	BoundingBoxPtr box;

	PhysicsPtr physics;

	TransformPtr transform;

	AnimationPtr animation;

	SpritePtr sprite;

  BehaviorPtr behavior;

	int health;

  float timer;
}GameObject;

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

// Dynamically allocate a clone of an existing game object.
// Params:
//	 other = Pointer to the game object to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned object,
//	   else return NULL.
GameObjectPtr GameObjectClone(const GameObjectPtr other)
{
  if (other)
  {
    GameObjectPtr gameObject = calloc(1, sizeof(GameObject));
    if (gameObject)
    {
      gameObject->name = other->name;
      gameObject->sprite = SpriteClone(other->sprite);
      gameObject->animation = AnimationClone(other->animation, gameObject->sprite);
      gameObject->behavior = BehaviorClone(other->behavior, gameObject);
      gameObject->isDestroyed = other->isDestroyed;
      gameObject->physics = PhysicsClone(other->physics);
      gameObject->transform = TransformClone(other->transform);
      return gameObject;
    }
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
    AnimationFree(&((*gameObject)->animation));
    FreePhysics(&(*gameObject)->physics);
    SpriteFree(&(*gameObject)->sprite);
    FreeTransform(&(*gameObject)->transform);
    FreeBoundingBox(&(*gameObject)->box);
    free(*gameObject);
    (*gameObject) = NULL;
	}
}

// Flag a game object for destruction.
// (Note: This is to avoid game objects being destroyed while they are being processed.)
// Params:
//	 gameObject = Pointer to the game object to be destroyed.
// Returns:
//	 If 'gameObject' is valid,
//	   then set the 'isDestroyed' boolean variable,
//	   else bail.
void GameObjectDestroy(GameObjectPtr gameObject)
{
  if (gameObject)
  {
    gameObject->isDestroyed = true;
  }
}

// Check whether a game object has been flagged for destruction.
// Params:
//	 gameObject = Pointer to the game object to be checked.
// Returns:
//	 If 'gameObject' is valid,
//	   then return the 'isDestroyed' boolean variable,
//	   else return false.
bool GameObjectIsDestroyed(GameObjectPtr gameObject)
{
  if (gameObject)
  {
    return gameObject->isDestroyed;
  }
  return false;
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

// Attach a behavior component to a game object.
// Params:
//	 gameObject = Pointer to the game object.
//   behavior = Pointer to the behavior component to be attached.
void GameObjectSetBehavior(GameObjectPtr gameObject, BehaviorPtr behavior)
{
  if (gameObject && behavior)
  {
    gameObject->behavior = behavior;
    gameObject->behavior->parent = gameObject;
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

// Get the game object's name.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the game object's name,
//		else return NULL.
const char * GameObjectGetName(const GameObjectPtr gameObject)
{
  if (gameObject)
  {
    return gameObject->name;
  }
  return NULL;
}

// Compare the game object's name with the specified name.
// Params:
//	 gameObject = Pointer to the game object.
//   name = Pointer to the name to be checked.
// Returns:
//	 If the game object pointer is valid,
//		then return true if the names match, false otherwise,
//		else return false.
bool GameObjectIsNamed(const GameObjectPtr gameObject, const char * name)
{
  if (gameObject)
  {
    if (strcmp(gameObject->name, name));
    {
      return false;
    }
  }
  return true;
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

// Get the behavior component attached to a game object.
// Params:
//	 gameObject = Pointer to the game object.
// Returns:
//	 If the game object pointer is valid,
//		then return a pointer to the attached behavior component,
//		else return NULL.
BehaviorPtr GameObjectGetBehavior(const GameObjectPtr gameObject)
{
  if (gameObject)
  {
    return gameObject->behavior;
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
  if (gameObject && gameObject->physics && gameObject->transform)
  {
    if (gameObject->animation)
    {
      AnimationUpdate(gameObject->animation, dt);
    }
    PhysicsUpdate(gameObject->physics, gameObject->transform, dt);
    BehaviorUpdate(gameObject->behavior, dt);
    UpdateBoundingBox(gameObject->box, GetOldTranslation(gameObject->physics));
  }
}
// Draw any visible components attached to the game object.
// (Hint: You will need to call SpriteDraw(), passing the sprite and transform components.)
// (NOTE: You must first check for valid pointers before calling this function.)
// Params:
//	 gameObject = Pointer to the game object.
void GameObjectDraw(GameObjectPtr gameObject)
{
  if (gameObject && gameObject->sprite && gameObject->transform)
  {
    SpriteDraw(gameObject->sprite, gameObject->transform);
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

GameObjectPtr GameObjectCreateTile(Vector2D scale, Vector2D position, AEGfxVertexList *  mesh, SpriteSourcePtr sSource, Vector2D halfsize)
{
	GameObjectPtr gObject = GameObjectCreate("Tile");
	GameObjectSetTransform(gObject, TransformCreate(0, 0));
	TransformSetScale(GameObjectGetTransform(gObject), scale);
	TransformSetRotation(GameObjectGetTransform(gObject), 0);
	TransformSetTranslation(GameObjectGetTransform(gObject), &position);
	SpritePtr EarthSprite = SpriteCreate("Tile Sprite");
	SpriteSetMesh(EarthSprite, mesh);
	SpriteSetSpriteSource(EarthSprite, sSource);
	GameObjectSetSprite(gObject, EarthSprite);
	GameObjectSetPhysics(gObject, PhysicsCreate());
	SetPhysicsTranslation(GameObjectGetPhysics(gObject), position);
	GameObjectSetBoundingBox(gObject, CreateBoundingBox(position, halfsize));
	HalfsizeScale(GameObjectGetBoundingBox(gObject), scale);

	return gObject;

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
