#include "GraphicsWindow.h"
#include "rendering/Renderer.h"
#include "rendering/Camera.h"
#include "Logger.h"
using namespace glm;
GraphicsWindow::GraphicsWindow(int windowWidth, int windowHeight, const char* title) : currentWidth(windowWidth), currentHeight(windowHeight), title(title)
{
	renderer = new Renderer();
	logger = new Logger();
	viewer = new Camera({ 0,0,0 });
}

GraphicsWindow::~GraphicsWindow()
{
	if (!isClosing)close();
	delete renderer;
	delete logger;
	delete viewer;
}

bool GraphicsWindow::init()
{
	if (hasInitialized)
	{
		logger->errorPrint("init() called on an already initialized GraphicsWindow object!");
		return false;
	}
	;
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

void GraphicsWindow::setViewerFarPlane(float far)
{
	viewer->setFarPlane(far);
}

void GraphicsWindow::setViewerNearPlane(float near)
{
	viewer->setNearPlane(near);
}

void GraphicsWindow::setViewerFov(float fov)
{
	viewer->setFov(fov);
}

void GraphicsWindow::setViewerPos(float x, float y, float z)
{
	viewer->setPos({ x,y,z });
}

void GraphicsWindow::offsetViewerPos(float x, float y, float z)
{
	viewer->addPos({ x,y,z });
}

void GraphicsWindow::rotateViewerPitch(float degrees)
{
	viewer->rotatePitch(degrees);
}

void GraphicsWindow::rotateViewerYaw(float degrees)
{
	viewer->rotateYaw(degrees);
}

void GraphicsWindow::onFixedUpdate(float timeStep)
{
	viewer->onFixedUpdate(timeStep);
}

void GraphicsWindow::onUpdateAndDraw(float lerpFactor)
{
	if (isClosing)
	{
		logger->errorPrint("drawAll() called on a closing GraphicsWindow object!");
		return;
	}
	viewer->onUpdate(lerpFactor);
	renderer->drawAll(windowHandle, viewer, lerpFactor);
	renderer->swapAndPoll(windowHandle);
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

void GraphicsWindow::requestRender(int renderType, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float r, float g, float b, float a)
{
	renderer->requestRender(renderType, { posX, posY, posZ }, { sizeX, sizeY, sizeZ }, { r,g,b,a });
}

void GraphicsWindow::requestRenderLerp(int renderType, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ, float r, float g, float b, float a, float prevPosX, float prevPosY, float prevPosZ, float prevSizeX, float prevSizeY, float prevSizeZ, float prevR, float prevG, float prevB, float prevA)
{
	renderer->requestRenderLerp(renderType, { posX, posY, posZ }, { sizeX, sizeY, sizeZ }, { r,g,b,a }, { prevPosX, prevPosY, prevPosZ }, { prevSizeX, prevSizeY, prevSizeZ }, { prevR,prevG,prevB,prevA });
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

bool GraphicsWindow::isWindowBeingClosed()
{
	if (isClosing) return true;
	return renderer->shouldWindowClose(windowHandle);
}

void GraphicsWindow::close()
{
	logger->notify("Closing graphics window..");
	isClosing = true;
	renderer->destroyWindow(windowHandle);
	renderer->close();
}
