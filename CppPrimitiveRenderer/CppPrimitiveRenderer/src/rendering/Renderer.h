#pragma once
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
};

