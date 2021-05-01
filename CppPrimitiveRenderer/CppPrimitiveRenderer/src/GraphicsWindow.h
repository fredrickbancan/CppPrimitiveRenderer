#pragma once
class GraphicsWindow
{
public:
	GraphicsWindow(int windowWidth, int windowHeight, const char* title);
	~GraphicsWindow();
	void init();
	void beginRenderRequests();
	void endRenderRequests();
	void drawAll();
	void close();
private:
	
	bool isClosing = false;
	bool hasInitialized = false;
	int currentWidth;
	int currentHeight;
	const char* title = nullptr;
	class Renderer* renderer = nullptr;
	class Logger* logger = nullptr;
	struct GLFWwindow* windowHandle = nullptr;
};