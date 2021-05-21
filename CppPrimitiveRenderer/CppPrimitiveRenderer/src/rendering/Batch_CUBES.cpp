#include "GL/glew.h"
#include "Batch_CUBES.h"
#include "VertexArrayObject.h"
#include "Shaders.h"
#include <iostream>
using namespace std;
Shader* Batch_CUBES::batchShader = nullptr;

Batch_CUBES::Batch_CUBES()
{
	renderType = RenderTypes::CUBES;
	vao = new VertexArrayObject();
	vao->beginBuilding();
	buildBatch();
	vao->finishBuilding();
}

void Batch_CUBES::reset()
{
	addedItter = 0;
	data.clear();
}

void Batch_CUBES::addToBatch(glm::vec3 pos, glm::vec3 size, glm::vec4 color)
{
	if (color.w <= 0.001F)return;
	for(int i = 0; i < 6; i++)
		data.push_back({ pos.x, pos.y, pos.z, size.x, size.y, size.z, color.x, color.y, color.z, color.w , (float)i});
	addedItter += 6;
}

void Batch_CUBES::addToBatchLerp(glm::vec3 pos, glm::vec3 size, glm::vec4 color, glm::vec3 prevPos, glm::vec3 prevSize, glm::vec4 prevColor)
{
	if (color.w <= 0.001F)return;
	for (int i = 0; i < 6; i++)
		data.push_back({ pos.x, pos.y, pos.z, size.x, size.y, size.z, color.x, color.y, color.z, color.w , (float)i });
	addedItter += 6;
}

bool Batch_CUBES::hasBeenUsedSinceLastUpdate()
{
	return addedItter > 0;
}

void Batch_CUBES::updateBuffers()
{
	//increase size of vbo if it is too small
	if (addedItter * CubeFace::sizeBytes >= currentBufferByteCapacity)
	{
		currentBufferByteCapacity += 2048 * CubeFace::sizeBytes;
		vao->resizeBuffer(0, currentBufferByteCapacity);
	}

	if (addedItter * 24 >= currentIndiciesMaxCount) 
	{
		currentIndiciesMaxCount += 2048 * 24;
		vao->resizeIndicesBuffer(currentIndiciesMaxCount);
		genIndices(indices, currentIndiciesMaxCount/4);
		vao->updateIndicesBuffer(&indices[0], currentIndiciesMaxCount);
	}

	vao->updateBuffer(0, (const void*)&data[0], addedItter * CubeFace::sizeBytes);
}

void Batch_CUBES::updateUniforms(glm::mat4x4 proj, glm::mat4x4 view, glm::vec2 viewPortSize, float lerpFactor)
{
	batchShader->bind();
	batchShader->setUniformMat4f("projMatrix", proj);
	batchShader->setUniformMat4f("viewMatrix", view);
	batchShader->setUniform2f("viewPortSize", viewPortSize);
	batchShader->setUniform1f("lerpFactor", lerpFactor);
}

void Batch_CUBES::drawBatch()
{
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	batchShader->bind();
	vao->bind();
	glDrawElements(GL_PATCHES, addedItter * 4, GL_UNSIGNED_INT, nullptr);
}

void Batch_CUBES::deleteBatch()
{
	delete vao;
}

void Batch_CUBES::loadShader(Logger* loggerRef)
{
	if (batchShader != nullptr)return;
	batchShader = new Shader("shaders/CUBES.shader", "shaders/CUBES_TESS.shader", loggerRef);
}

void Batch_CUBES::deleteShader()
{
	if (batchShader == nullptr)return;
	delete batchShader;
	batchShader = nullptr;
}

void Batch_CUBES::buildBatch()
{
	VertexBufferLayout vbl = VertexBufferLayout();
	vbl.add(GL_FLOAT, 3, false);
	vbl.add(GL_FLOAT, 3, false);
	vbl.add(GL_FLOAT, 4, false);
	vbl.add(GL_FLOAT, 1, false);
	currentBufferByteCapacity = 2048;
	currentIndiciesMaxCount = 2048 * 24;
	vao->addDynamicIndicesBuffer(2048 * 24);
	genIndices(indices, (2048 * 24)/4);
	vao->updateIndicesBuffer(&indices[0], 2048 * 24);
	vao->addDynamicBuffer(currentBufferByteCapacity, vbl);
}

void Batch_CUBES::genIndices(std::vector<unsigned int>& data, unsigned int count)
{
	data.clear();
	for (unsigned int i = 0U; i < count * 4U; i+= 4U)
	{
		unsigned int index = i / 4U;
		for (unsigned int j = 0U; j < 4U; j++)
		{
			data.push_back(index);
		}
	}
}
