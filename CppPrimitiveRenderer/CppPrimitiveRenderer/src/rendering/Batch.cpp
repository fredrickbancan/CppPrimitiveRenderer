#include "Batch.h"
#include "VertexArrayObject.h"
Batch::Batch(int renderType) : renderType(renderType)
{
	vao = new VertexArrayObject();
	vao->beginBuilding();
	buildBatch();
	vao->finishBuilding();
}