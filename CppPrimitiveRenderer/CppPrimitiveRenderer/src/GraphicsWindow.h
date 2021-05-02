#pragma once
class GraphicsWindow
{
public:
	GraphicsWindow(int windowWidth, int windowHeight, const char* title);
	~GraphicsWindow();
	bool init();
	void beginRenderRequests();
	void endRenderRequests();
	void drawAll();
	bool isWindowBeingClosed();
	void close();

	struct GLFWwindow* getGLFWWindowHandle() const { return windowHandle; }
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