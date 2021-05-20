#pragma once
class GraphicsWindow
{
public:
	GraphicsWindow(int windowWidth, int windowHeight, const char* title);
	~GraphicsWindow();
	bool init();
	void setViewerFarPlane(float far);
	void setViewerNearPlane(float near);
	void setViewerFov(float fov);
	void setViewerPos(float x, float y, float z);
	void offsetViewerPos(float x, float y, float z);
	void rotateViewerPitch(float degrees);
	void rotateViewerYaw(float degrees);
	void onFixedUpdate(float timeStep);
	void onUpdateAndDraw(float lerpFactor);
	void beginRenderRequests();
	void requestRender(int renderType, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float r, float g, float b, float a);
	void requestRenderLerp(int renderType, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float r, float g, float b, float a, float prevPosX, float prevPosY, float prevPosZ, float prevSizeX, float prevSizeY, float prevSizeZ, float prevR, float prevG, float prevB, float prevA);
	void endRenderRequests();
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
	class Camera* viewer = nullptr;
	struct GLFWwindow* windowHandle = nullptr;
};