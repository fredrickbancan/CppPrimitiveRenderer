#include "GL/glew.h"
#include "Batch_POINT_SPHERES.h"
#include "VertexArrayObject.h"
#include "Shaders.h"

Shader* Batch_POINT_SPHERES::batchShader = nullptr;

Batch_POINT_SPHERES::Batch_POINT_SPHERES()
{
	renderType = RenderTypes::POINT_SPHERES;
	vao = new VertexArrayObject();
	vao->beginBuilding();
	buildBatch();
	vao->finishBuilding();
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

void Batch_POINT_SPHERES::addToBatch(glm::vec3 pos, glm::vec3 size, glm::vec4 color)
{
	if (color.w <= 0.001F)return;
	data.push_back({pos.x, pos.y, pos.z, size.x, color.x, color.y, color.z, color.w});
	addedItter++;
}

void Batch_POINT_SPHERES::addToBatchLerp(glm::vec3 pos, glm::vec3 size, glm::vec4 color, glm::vec3 prevPos, glm::vec3 prevSize, glm::vec4 prevColor)
{
	if (color.w <= 0.001F)return;
	data.push_back({ pos.x, pos.y, pos.z, size.x, color.x, color.y, color.z, color.w});
	addedItter++;
}

bool Batch_POINT_SPHERES::hasBeenUsedSinceLastUpdate()
{
	return addedItter > 0;
}

void Batch_POINT_SPHERES::updateBuffers()
{
	//increase size of vbo if it is too small
	if (addedItter * PointSphere::sizeBytes >= currentBufferByteCapacity)
	{
		currentBufferByteCapacity += 2048;
		vao->resizeBuffer(0, currentBufferByteCapacity);
	}

	vao->updateBuffer(0, (const void*)&data[0], addedItter * PointSphere::sizeBytes);
}

void Batch_POINT_SPHERES::updateUniforms(glm::mat4x4 proj, glm::mat4x4 view, glm::vec2 viewPortSize, float lerpFactor)
{
	batchShader->bind();
	batchShader->setUniformMat4f("projMatrix", proj);
	batchShader->setUniformMat4f("viewMatrix", view);
	batchShader->setUniform2f("viewPortSize", viewPortSize);
	batchShader->setUniform1f("lerpFactor", lerpFactor);
}

void Batch_POINT_SPHERES::drawBatch()
{
	batchShader->bind();
	vao->bind();
	glDrawArrays(GL_POINTS, 0, addedItter);
}

void Batch_POINT_SPHERES::loadShader(class Logger* loggerRef)
{
	if (batchShader != nullptr)return;
	batchShader = new Shader("shaders/POINT_SPHERES.shader", loggerRef);
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
	vbl.add(GL_FLOAT, 4, false);
	currentBufferByteCapacity = 2048;
	vao->addDynamicBuffer(currentBufferByteCapacity, vbl);
}
