#pragma once
#include "Batch.h"
#include <unordered_map>
class Renderer
{
public:
	Renderer();
	~Renderer();
	struct GLFWwindow* init(int windowWidth, int windowHeight, const char* title);
	void beginRenderRequests();
	void endRenderRequests();
	void drawAll();
	void close();
private:
	class Logger* logger = nullptr;
	bool hasInitialized = false;
	std::unordered_map<int, Batch> batches;
};

