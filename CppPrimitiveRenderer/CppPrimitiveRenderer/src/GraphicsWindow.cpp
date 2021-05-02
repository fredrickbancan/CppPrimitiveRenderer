#include <GLFW/glfw3.h>
#include "GraphicsWindow.h"
#include "rendering/Renderer.h"
#include "Logger.h"
GraphicsWindow::GraphicsWindow(int windowWidth, int windowHeight, const char* title) : currentWidth(windowWidth), currentHeight(windowHeight), title(title)
{
	renderer = new Renderer();
	logger = new Logger();
}

GraphicsWindow::~GraphicsWindow()
{
	if (!isClosing)close();
	delete renderer;
	delete logger;
}

bool GraphicsWindow::init()
{
	if (hasInitialized)
	{
		logger->errorPrint("init() called on an already initialized GraphicsWindow object!");
		return false;
	}
	logger->notify("Initializing Graphics Window...");
	windowHandle = renderer->init(currentWidth, currentHeight, title);
	if (!windowHandle)
	{
		close();
		return false;
	}
	hasInitialized = true;
	return true;
}

void GraphicsWindow::beginRenderRequests()
{
	if (isClosing)
	{
		logger->errorPrint("beginRenderRequests() called on a closing GraphicsWindow object!");
		return;
	}
	renderer->beginRenderRequests();
}

void GraphicsWindow::endRenderRequests()
{
	if (isClosing)
	{
		logger->errorPrint("endRenderRequests() called on a closing GraphicsWindow object!");
		return;
	}
	renderer->endRenderRequests();
}

void GraphicsWindow::drawAll()
{
	if (isClosing)
	{
		logger->errorPrint("drawAll() called on a closing GraphicsWindow object!");
		return;
	}

	renderer->drawAll();
	/* Swap front and back buffers */
	glfwSwapBuffers(windowHandle);
	/* Poll for and process events */
	glfwPollEvents();
}

bool GraphicsWindow::isWindowBeingClosed()
{
	if (isClosing) return true;
	return glfwWindowShouldClose(windowHandle) > 0;
}

void GraphicsWindow::close()
{
	logger->notify("Closing graphics window..");
	isClosing = true;
	glfwDestroyWindow(windowHandle);
	renderer->close();
}
