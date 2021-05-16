#pragma once
#include <unordered_map>
#include <memory>
#include "../glm/mat4x4.hpp"
#include "../glm/vec3.hpp"
class Renderer
{
public:
	Renderer();
	~Renderer();
	struct GLFWwindow* init(int windowWidth, int windowHeight, const char* title);
	void beginRenderRequests();
	void requestRender(int renderType, glm::vec3 pos, glm::vec3 size, glm::vec4 color);
	void requestRenderLerp(int renderType, glm::vec3 pos, glm::vec3 size, glm::vec4 color, glm::vec3 prevPos, glm::vec3 prevSize, glm::vec4 prevColor);
	void endRenderRequests();
	void drawAll(class Camera* viewer, float lerpFactor);
	void swapAndPoll(struct GLFWwindow* windowHandle);
	bool shouldWindowClose(struct GLFWwindow* windowHandle);
	void destroyWindow(struct GLFWwindow* windowHandle);
	void close();
private:
	class Logger* logger = nullptr;
	bool hasInitialized = false;
	std::unordered_map<int, class Batch*> batches;
};

