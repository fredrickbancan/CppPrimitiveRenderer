#pragma once
#include "../RenderTypes.h"
#include "../glm/mat4x4.hpp"
#include "../glm/vec3.hpp"
class Batch
{
public:
	Batch(int renderType);
	virtual ~Batch() = 0;
	virtual void reset() = 0;
	virtual void addToBatch(glm::vec3 pos, glm::vec3 size, glm::vec4 color, glm::vec3* prevPos = nullptr, glm::vec3* prevSize = nullptr, glm::vec4* prevColor = nullptr) = 0;
	virtual bool hasBeenUsedSinceLastUpdate() = 0;
	virtual void updateBuffers() = 0;
	virtual void updateUniforms(glm::mat4x4 proj, glm::mat4x4 view, float lerpFactor = 1.0F) = 0;
	virtual void drawBatch() = 0;
	virtual void deleteBatch() = 0;
	int getRenderType() const { return renderType; }
protected:
	virtual void buildBatch() = 0;
	int renderType = RenderTypes::NULL_TYPE;
	class VertexArrayObject* vao;
};