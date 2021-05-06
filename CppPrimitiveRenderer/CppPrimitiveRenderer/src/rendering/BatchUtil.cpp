#include "BatchUtil.h"
#include "Batch.h"
#include "Batch_POINT_SPHERES.h"	

Batch* BatchUtil::makeBatch(int renderType)
{
	switch (renderType)
	{
	case RenderTypes::NULL_TYPE:
		return nullptr;
	case RenderTypes::POINT_SPHERES:
		return new Batch_POINT_SPHERES();
	default:
		return nullptr;
	}
}

void BatchUtil::loadAllShaders(Logger* loggerRef)
{
	Batch_POINT_SPHERES::loadShader(loggerRef);
}

void BatchUtil::deleteAllShaders()
{
	Batch_POINT_SPHERES::deleteShader();
}