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

void GraphicsWindow::init()
{
	if (hasInitialized)
	{
		logger->errorPrint("init() called on an already initialized GraphicsWindow object!");
		return;
	}
	logger->notify("Initializing Graphics Window...");
	renderer->init(currentWidth, currentHeight, title);
	if (!renderer)
	{
		close();
		return;
	}
	hasInitialized = true;
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
}

void GraphicsWindow::close()
{
	logger->notify("Closing graphics window..");
	isClosing = true;
	renderer->close();
}
