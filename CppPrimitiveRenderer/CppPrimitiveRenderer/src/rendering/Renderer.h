#pragma once
#include <unordered_map>
#include <memory>
#include "../glm/mat4x4.hpp"
#include "../glm/vec3.hpp"
#include "../glm/vec2.hpp"
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
	void drawAll(struct GLFWwindow* windowHandle, class Camera* viewer, float lerpFactor);
	void setClearColor(glm::vec3 color);
	void swapAndPoll(struct GLFWwindow* windowHandle);
	bool shouldWindowClose(struct GLFWwindow* windowHandle);
	void destroyWindow(struct GLFWwindow* windowHandle);
	glm::vec2 getViewPortSize(GLFWwindow* windowHandle);
	void close();
private:
	class Logger* logger = nullptr;
	bool hasInitialized = false;
	glm::vec2 viewPortSize = {100,100};
	glm::vec3 clearColor = {0,0,0};
	std::unordered_map<int, class Batch*> batches;
};

