#pragma once
#include "Batch.h"
#include <vector>
#include "PointSphere.h"
class Batch_POINT_SPHERES : public Batch
{
public:
	Batch_POINT_SPHERES();
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
	std::vector<PointSphere> data;
	int addedItter = 0;
	static class Shader* batchShader;
};