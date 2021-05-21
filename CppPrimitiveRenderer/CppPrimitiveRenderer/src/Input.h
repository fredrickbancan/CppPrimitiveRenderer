#pragma once

/*Class for basic GLFW input queries. User must include InputCodes.h and use the codes there for these functions.
InputCodes.h is extracted from GLFW library.*/
class Input
{
public:
	/*Construct this input object with an existing graphics window handle. If this class has a null pointer, will return false for all bool functions.*/
	Input(struct GLFWwindow* relevantWindowHandle);
	~Input();

	/*returns true if key is down*/
	bool isKeyDown(int keyCode);

	/*returns true if mouse button is down*/
	bool isMouseButtonDown(int keyCode);

	/*Provides the window x,y coord of the cursor*/
	void getMouseXY(double* x, double* y);

	/*Provides the x and y deltas of the cursor*/
	void getMouseDeltas(double* dX, double* dY);

	/*Calling with true will cause the cursor to be constrained to the window*/
	void setGrabMouse(bool grab);

	/*Calling with false will cause the cursor to be invisible within the window.*/
	void setMouseVisible(bool visible);

	/*Changes the relative window pointer to the provided one.*/
	void setRelevantWindow(struct GLFWwindow* relevantWindowHandle);

	/*Should be called at the start of each frame before calling mouse related functions.*/
	void update();

private:
	/*centers the cursor in the middle of the window.*/
	void centerMouse();
	struct GLFWwindow* relevantWindow = nullptr;
	bool cursorGrabbed = false;
	double mouseX;
	double mouseY;
	double prevMouseX;
	double prevMouseY;
	double mouseDeltaX;
	double mouseDeltaY;
};