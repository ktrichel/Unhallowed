#include "stdafx.h"
#include "GameObjectFactory.h"
#include <AEEngine.h>

typedef struct GameObjectFactory
{
	int objectCount;

	GameObjectPtr gameObjects[200];
} GameObjectFactory;

static GameObjectFactory tiles;

void GameObjectFactoryFree()
{
	while (tiles.objectCount > 0)
	{
		GameObjectFree(&tiles.gameObjects[tiles.objectCount]);
		--tiles.objectCount;
	}
}

void GameObjectFactoryAdd(GameObjectPtr gameObject)
{
	if (gameObject)
	{
		int value;
		value = tiles.objectCount++;
		tiles.gameObjects[value] = gameObject;
	}
}

void GameObjectFactoryDraw()
{
	int i = 0;

	while (i < tiles.objectCount)
	{
		GameObjectDraw(tiles.gameObjects[i]);
		++i;
	}
}

void GameObjectFactoryUpdate(float dt)
{

	int i = 0;

	for (i = 0; i <= tiles.objectCount; ++i)
	{
		GameObjectUpdate(tiles.gameObjects[i], dt);
		/*
		if (GameObjectIsDestroyed(gameObjectActiveList.objectList[i]))
		{
			GameObjectFree(&gameObjectActiveList.objectList[i]);
			for (j = i; j < gameObjectActiveList.objectCount; ++j)
			{
				gameObjectActiveList.objectList[j] = gameObjectActiveList.objectList[j + 1];
			}
			GameObjectFree(&gameObjectActiveList.objectList[j]);
			gameObjectActiveList.objectCount--;
			i--;
		}
		*/
	}
}

GameObjectPtr GameObjectFactoryCollision(GameObjectPtr object)
{
	int i = 0;

	for (i = 0; i < tiles.objectCount; ++i)
	{
		if (CollisionCheck(GameObjectGetBoundingBox(object), GameObjectGetBoundingBox(tiles.gameObjects[i])))
			return tiles.gameObjects[i];
	}
	return NULL;
}
