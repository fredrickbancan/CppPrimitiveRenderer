#include "Batch_POINT_SPHERES.h"
#include "VertexArrayObject.h"
#include "GLFW/glfw3.h"

Batch_POINT_SPHERES::Batch_POINT_SPHERES() : Batch(RenderTypes::POINT_SPHERES)
{
	
}

void Batch_POINT_SPHERES::deleteBatch()
{
	delete vao;
}

void Batch_POINT_SPHERES::reset()
{
	addedItter = 0;
	data.clear();
}

void Batch_POINT_SPHERES::addToBatch(glm::vec3 pos, glm::vec3 size, glm::vec4 color, glm::vec3* prevPos, glm::vec3* prevSize, glm::vec4* prevColor)
{
	data.push_back({pos.x, pos.y, pos.z, size.x, color.x, color.y, color.z});
	addedItter++;
}

bool Batch_POINT_SPHERES::hasBeenUsedSinceLastUpdate()
{
	return addedItter > 0;
}

void Batch_POINT_SPHERES::updateBuffers()
{
	vao->updateBuffer(0, (const void*)&data[0], addedItter * PointSphere::sizeBytes);
}

void Batch_POINT_SPHERES::updateUniforms(glm::mat4x4 proj, glm::mat4x4 view, float lerpFactor)
{

}

void Batch_POINT_SPHERES::drawBatch()
{
	vao->bind();
	glDrawArrays(GL_POINTS, 0, addedItter);
}

void Batch_POINT_SPHERES::buildBatch()
{
	VertexBufferLayout vbl = VertexBufferLayout();
	vbl.add(GL_FLOAT, 3, false);
	vbl.add(GL_FLOAT, 1, false);
	vbl.add(GL_FLOAT, 3, false);
	vao->addDynamicBuffer(2048, vbl);
}
