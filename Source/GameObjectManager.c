//------------------------------------------------------------------------------
//
// File Name:	GameObjectManager.c
// Author(s):	Kyle Trichel (kyle.trichel)
// Project:		MyGame
// Course:		CS230S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObjectManager.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

#define objectListSize 100

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct GameObjectManager
{
  // The current number of game objects currently in the list.
  unsigned int objectCount;

  // The maximum number of game objects ever in the list, at any given moment.
  unsigned int objectMax;

  // This list can be a fixed-length array (minimum size of 100 entries)
  // or a dynamically sized array, such as a linked list.
  GameObjectPtr	objectList[objectListSize];

} GameObjectManager;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static GameObjectManager gameObjectActiveList;
static GameObjectManager gameObjectArchetypes;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
void AddToList(GameObjectManager *list, GameObjectPtr gameObject);
GameObjectPtr FindName(const GameObjectManager *list, const char * name);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the game object manager.
// (NOTE: This function should initialize the lists for both active game objects
//    and the archetype objects.)
void GameObjectManagerInit(void)
{
  gameObjectActiveList.objectCount = 0;
  gameObjectActiveList.objectMax = objectListSize;
  for (unsigned int i = 0; i < gameObjectActiveList.objectMax; i++)
  {
    gameObjectActiveList.objectList[i] = NULL;
  }

  gameObjectArchetypes.objectCount = 0;
  gameObjectArchetypes.objectMax = objectListSize;
  for (unsigned int i = 0; i < gameObjectArchetypes.objectMax; i++)
  {
    gameObjectArchetypes.objectList[i] = NULL;
  }
}

// Update all objects in the active game objects list.
// (NOTE: After a game object has been updated, if it has been flagged as
//    destroyed, then it must be removed from the list and freed properly.
//    Additionally, the count of active objects must be reduced by 1.)
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameObjectManagerUpdate(float dt)
{
  for (unsigned int i = 0; i < gameObjectActiveList.objectMax; i++)
  {
    GameObjectUpdate(gameObjectActiveList.objectList[i], dt);

    if (GameObjectIsDestroyed(gameObjectActiveList.objectList[i]))
    {
      GameObjectFree(&gameObjectActiveList.objectList[i]);
      gameObjectActiveList.objectList[i] = NULL;
      gameObjectActiveList.objectCount--;
    }
  }
}

// Draw all game objects in the active game object list.
void GameObjectManagerDraw(void)
{
  for (unsigned int i = 0; i < gameObjectActiveList.objectMax; i++)
  {
    GameObjectDraw(gameObjectActiveList.objectList[i]);
  }
}

// Shutdown the game object manager.
// (NOTE: This means removing all game objects from both the active and
//	  archetype game object lists.  Make sure that the object counts are
//	  properly updated in both situations.)
void GameObjectManagerShutdown(void)
{
  for (unsigned int i = 0; i < gameObjectActiveList.objectMax; i++)
  {
    GameObjectFree(&gameObjectActiveList.objectList[i]);
    gameObjectActiveList.objectList[i] = NULL;
    gameObjectActiveList.objectCount--;
  }
  for (unsigned int i = 0; i < gameObjectArchetypes.objectMax; i++)
  {
    GameObjectFree(&(gameObjectArchetypes.objectList[i]));
    gameObjectActiveList.objectList[i] = NULL;
    gameObjectArchetypes.objectCount--;
  }
}

// Add a game object to the active game object list.
// (Hint: This function and the GameObjectManagerAddArchetype functions require
//    the same code.  Consider creating a single function that adds an object
//	  to a list that is passed as a parameter.)
// Params:
//	 gameObject = Pointer to the game object to be added to the list.
void GameObjectManagerAdd(GameObjectPtr gameObject)
{
  AddToList(&gameObjectActiveList, gameObject);
}

// Add a game object to the game object archetype list.
// (Hint: This function and the GameObjectManagerAdd functions require
//    the same code.  Consider creating a single, private function that adds
//	 an object to a list that is passed as a parameter.)
// Params:
//	 gameObject = Pointer to the game object to be added to the list.
void GameObjectManagerAddArchetype(GameObjectPtr gameObject)
{
  AddToList(&gameObjectArchetypes, gameObject);
}

// Returns a pointer to the first active game object matching the specified name.
// (Hint: This function and the GameObjectManagerGetObjectByName functions require
//    the same code.  Consider creating a single, private function that searches
//	  for the named game object in a list that is passed as a parameter.)
// Params:
//	 name = The name of the archetype to be returned, if found.
// Returns:
//   If the named archetype is found,
//	   then return the pointer to the named game object archetype,
//	   else return NULL.
GameObjectPtr GameObjectManagerGetObjectByName(const char * name)
{
  return FindName(&gameObjectActiveList, name);
}

// Returns a pointer to the first game object archetype matching the specified name.
// (Hint: This function and the GameObjectManagerGetObjectByName functions require
//    the same code.  Consider creating a single, private function that searches
//	  for the named game object in a list that is passed as a parameter.)
// Params:
//	 name = The name of the archetype to be returned, if found.
// Returns:
//   If the named archetype is found,
//	   then return the pointer to the named game object archetype,
//	   else return NULL.
GameObjectPtr GameObjectManagerGetArchetype(const char * name)
{
  return FindName(&gameObjectArchetypes, name);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void AddToList(GameObjectManager *list, GameObjectPtr gameObject)
{
  if (gameObject && list)
  {
    unsigned int i = 0;
    while (i < list->objectMax)
    {
      if (list->objectList[i] == NULL)
      {
        list->objectList[i] = gameObject;
        return;
      }
      i++;
    }
  }
}

GameObjectPtr FindName(const GameObjectManager *list, const char * name)
{
  if (name && list)
  {
    for (unsigned int i = 0; i < list->objectMax; i++)
    {
      if (!strcmp(GameObjectGetName(list->objectList[i]), name))
      {
        return list->objectList[i];
      }
    }
  }
  return NULL;
}