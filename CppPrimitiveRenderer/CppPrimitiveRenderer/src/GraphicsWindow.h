#pragma once

struct GLFWwindow;
/*Abstract object providing basic functions for basic rendering and user input.*/
class GraphicsWindow
{
public:
	GraphicsWindow(int windowWidth, int windowHeight, const char* title);
	~GraphicsWindow();

	/*Must be called before any other functions. Returns true apon successful initialization. If init() returns false, user must call close() and/or delete this window.*/
	bool init();

	/*sets the far plane distance of the perspective camera*/
	void setViewerFarPlane(float far);

	/*sets the near plane distance of the perspective camera*/
	void setViewerNearPlane(float near);

	/*sets the fov of the perspective camera in degrees*/
	void setViewerFov(float fov);

	/*sets the position of the perspective camera in world space*/
	void setViewerPos(float x, float y, float z);

	/*adds the provided distances to the perspective camera's current position*/
	void offsetViewerPos(float x, float y, float z);

	/*moves the perspective camera in its facing direction by the provided distance. Negative value moves viewer backwards.*/
	void moveViewerFowards(float distance);

	/*Moves the perspective camera upwards relative to world. Negative value moves viewer downwards.*/
	void moveViewerUpwards(float distance);

	/*moves the perspective camera to its right based on facing direction. Negative value moves the viewer left.*/
	void strafeViewerRight(float distance);

	/*adds the provided degrees to the perspective cameras pitch rotation*/
	void rotateViewerPitch(float degrees);

	/*adds the provided degrees to the perspective cameras yaw rotation*/
	void rotateViewerYaw(float degrees);

	/*Gives the xyz values of the perspective camera's position*/
	void getViewerPos(float* x, float* y, float* z);

	/*Gives the xyz values of the perspective camera's front vector*/
	void getViewerFrontDirection(float* x, float* y, float* z);

	/*updates certain logic for camera. Call before any camera manipulations in a fixed update.*/
	void onFixedUpdate(float timeStep);

	/*Renders all primitives requested in the previous render update, and then swaps gl buffers and calls gl poll events. lerpFactor is value ranging 0-1 representing the progress between the previous fixed update/render update and the current. Is used to interpolate between render updates/fixed updates.*/
	void onUpdateAndDraw(float lerpFactor);

	/*Must be called at beginning of fixed update/render update before requesting render of any primitives.*/
	void beginRenderRequests();

	/*Adds a primitive of the requiested renderType to be rendered based on all of the provided values.*/
	void requestRender(int renderType, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float r, float g, float b, float a);

	/*Adds a primitive of the requiested renderType to be rendered with all of the provided values linearly interpolated between the "prev" values and the current ones. Only works with renderType's containing the key word "lerp". Non-lerp renderTypes use half the memory. Any non-lerp renderTypes called with this function will have no difference.*/
	void requestRenderLerp(int renderType, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float r, float g, float b, float a, float prevPosX, float prevPosY, float prevPosZ, float prevSizeX, float prevSizeY, float prevSizeZ, float prevR, float prevG, float prevB, float prevA);
	
	/*Must be called at the end of fixed update/render update after all primitives have been requested.*/
	void endRenderRequests();

	/*Sets the color of the clearing background. Default is black (0,0,0).*/
	void setBackgroundColor(float r, float g, float b);

	/*returns true if this window is being closed by the user or other application. For example, pressing the close button.*/
	bool isWindowBeingClosed();

	/*MUST be called before closing application. Frees all memory and render objects. Not calling this function will cause a memory leak!. Called by this windows destructor if it has not already been called..*/
	void close();

	/*Returns the GLFW window pointer for this window. User applications must include the glfw library to define this struct type.*/
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