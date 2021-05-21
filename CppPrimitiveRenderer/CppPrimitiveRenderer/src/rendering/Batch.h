#pragma once
#include "../RenderTypes.h"
#include "../glm/mat4x4.hpp"
#include "../glm/vec2.hpp"
#include "../glm/vec3.hpp"
class Batch
{
public:
	virtual void reset() = 0;
	virtual void addToBatch(glm::vec3 pos, glm::vec3 size, glm::vec4 color) = 0;
	virtual void addToBatchLerp(glm::vec3 pos, glm::vec3 size, glm::vec4 color, glm::vec3 prevPos, glm::vec3 prevSize, glm::vec4 prevColor) = 0;
	virtual bool hasBeenUsedSinceLastUpdate() = 0;
	virtual void updateBuffers() = 0;
	virtual void updateUniforms(glm::mat4x4 proj, glm::mat4x4 view, glm::vec2 viewPortSize, float lerpFactor = 1.0F) = 0;
	virtual void drawBatch() = 0;
	virtual void deleteBatch() = 0;
	int getRenderType() const { return renderType; }
protected:
	virtual void buildBatch() = 0;
	int renderType = RenderTypes::NULL_TYPE;
	unsigned int currentBufferByteCapacity = 0;
	class VertexArrayObject* vao = nullptr;
};