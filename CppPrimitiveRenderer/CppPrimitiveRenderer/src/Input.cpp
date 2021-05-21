#include "Input.h"
#include "GLFW/glfw3.h"
Input::Input(GLFWwindow* relevantWindow) : relevantWindow(relevantWindow)
{
	
}

Input::~Input()
{
}

bool Input::isKeyDown(int keyCode)
{
	if (relevantWindow == nullptr)return false;
	int state = glfwGetKey(relevantWindow, keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isMouseButtonDown(int keyCode)
{
	if (relevantWindow == nullptr)return false;
	int state = glfwGetMouseButton(relevantWindow, keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

void Input::getMouseXY(double* x, double* y)
{
	*x = mouseX;
	*y = mouseY;
}

void Input::getMouseDeltas(double* dX, double* dY)
{
	*dX = mouseDeltaX;
	*dY = mouseDeltaY;
}

void Input::setGrabMouse(bool grab)
{
	cursorGrabbed = grab;
}

void Input::setMouseVisible(bool visible)
{
	if (relevantWindow == nullptr)return;
	glfwSetInputMode(relevantWindow, GLFW_CURSOR, (visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN));
}

void Input::centerMouse()
{
	if (relevantWindow == nullptr)return;
	int w, h;
	glfwGetWindowSize(relevantWindow, &w, &h);
	glfwSetCursorPos(relevantWindow, (w/=2), (h/=2));
	prevMouseX = mouseX = w;
	prevMouseY = mouseY = h;
}

void Input::setRelevantWindow(GLFWwindow* relevantWindowHandle)
{
	relevantWindow = relevantWindowHandle;
}

void Input::update()
{
	if (relevantWindow == nullptr)return;
	prevMouseX = mouseX;
	prevMouseY = mouseY;
	glfwGetCursorPos(relevantWindow, &mouseX, &mouseY);
	mouseDeltaX = mouseX - prevMouseX;
	mouseDeltaY = mouseY - prevMouseY;
	if (cursorGrabbed)centerMouse();
}