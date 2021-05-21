#pragma once
#include "Batch.h"
#include "CubeFace.h"
#include <vector>
class Batch_CUBES : public Batch
{
public:
	Batch_CUBES();
	void reset() override;
	void addToBatch(glm::vec3 pos, glm::vec3 size, glm::vec4 color) override;
	void addToBatchLerp(glm::vec3 pos, glm::vec3 size, glm::vec4 color, glm::vec3 prevPos, glm::vec3 prevSize, glm::vec4 prevColor) override;
	bool hasBeenUsedSinceLastUpdate() override;
	void updateBuffers() override;
	void updateUniforms(glm::mat4x4 proj, glm::mat4x4 view, glm::vec2 viewPortSize, float lerpFactor = 1.0F) override;
	void drawBatch() override;
	void deleteBatch() override;
	static void loadShader(class Logger* loggerRef);
	static void deleteShader();
protected:
	void buildBatch() override;
private:
	static void genIndices(std::vector<unsigned int>& data, unsigned int count);
	std::vector<CubeFace> data;
	std::vector<unsigned int> indices;
	unsigned int addedItter = 0;
	unsigned int currentIndiciesMaxCount = 0;
	static class Shader* batchShader;
};