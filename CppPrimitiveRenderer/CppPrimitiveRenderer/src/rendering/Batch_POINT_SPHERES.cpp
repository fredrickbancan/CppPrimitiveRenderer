#include "Batch_POINT_SPHERES.h"
#include "VertexArrayObject.h"
#include "GLFW/glfw3.h"
#include "Shaders.h"

Shader* Batch_POINT_SPHERES::batchShader = nullptr;

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
	batchShader->bind();
	vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Batch_POINT_SPHERES::loadShader(class Logger* loggerRef)
{
	if (batchShader != nullptr)return;
	batchShader = new Shader("res/HelloTriangle.shader", loggerRef);
}

void Batch_POINT_SPHERES::deleteShader()
{
	if (batchShader == nullptr)return;
	delete batchShader;
	batchShader = nullptr;
}

void Batch_POINT_SPHERES::buildBatch()
{
	VertexBufferLayout vbl = VertexBufferLayout();
	vbl.add(GL_FLOAT, 3, false);
	vbl.add(GL_FLOAT, 1, false);
	vbl.add(GL_FLOAT, 3, false);
	vao->addDynamicBuffer(2048, vbl);
}
