#include "stdafx.h"
#include "Mesh.h"
#include <AEEngine.h>

AEGfxVertexList * MeshCreateQuad(float xHalfSize, float yHalfSize, float uSize, float vSize, const char * name)
{
	AEGfxMeshStart();

	AEGfxTriAdd(-xHalfSize, -yHalfSize, 0xFF00FFFF, 0.0f, vSize,
				xHalfSize, -yHalfSize, 0xFFFF00FF, uSize, vSize,
				-xHalfSize, yHalfSize, 0xFFFFFF00, 0.0f, 0.0f);

	AEGfxTriAdd(xHalfSize, -yHalfSize, 0xFFFF0000, uSize, vSize,
				xHalfSize, yHalfSize, 0xFF0000FF, uSize, 0.0f,
				-xHalfSize, yHalfSize, 0xFF00FF00, 0.0f, 0.0f);

	AEGfxVertexList* pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh, "Failed to create mesh %s!", name);

	return pMesh;
}