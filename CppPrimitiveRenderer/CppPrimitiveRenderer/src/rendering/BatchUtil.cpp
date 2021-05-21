#include "BatchUtil.h"
#include "Batch.h"
#include "Batch_POINT_SPHERES.h"	
#include "Batch_CUBES.h"

Batch* BatchUtil::makeBatch(int renderType)
{
	switch (renderType)
	{
	case RenderTypes::NULL_TYPE:
		return nullptr;
	case RenderTypes::POINT_SPHERES:
		return new Batch_POINT_SPHERES();
	case RenderTypes::CUBES:
		return new Batch_CUBES();
	default:
		return nullptr;
	}
}

void BatchUtil::loadAllShaders(Logger* loggerRef)
{
	Batch_POINT_SPHERES::loadShader(loggerRef);
	Batch_CUBES::loadShader(loggerRef);
}

void BatchUtil::deleteAllShaders()
{
	Batch_POINT_SPHERES::deleteShader();
	Batch_CUBES::deleteShader();
}