#pragma once
#include "Batch.h"
#include <vector>
#include "PointSphere.h"
class Batch_POINT_SPHERES : public Batch
{
public:
	Batch_POINT_SPHERES();
    void deleteBatch() override;
	void reset() override;
	void addToBatch(glm::vec3 pos, glm::vec3 size, glm::vec4 color, glm::vec3* prevPos = nullptr, glm::vec3* prevSize = nullptr, glm::vec4* prevColor = nullptr) override;
	bool hasBeenUsedSinceLastUpdate() override;
	void updateBuffers() override;
	void updateUniforms(glm::mat4x4 proj, glm::mat4x4 view, float lerpFactor = 1.0F) override;
	void drawBatch() override;
protected:
	void buildBatch() override;
private:
	std::vector<PointSphere> data;
	int addedItter = 0;
};