#include "GraphicsWindow.h"
#include "RenderTypes.h"
int main(void)
{
	GraphicsWindow* test = new GraphicsWindow(1920, 1080, "Hello World!");
	if (!test->init())
	{
		test->close();
		delete test;
		return -1;
	}
	while (!test->isWindowBeingClosed())
	{
		test->beginRenderRequests();
		test->requestRender(RenderTypes::POINT_SPHERES, 0, 0, -15, 0.5F, 0, 0, 0.3F, 0.5F, 1, 1);
		test->requestRender(RenderTypes::POINT_SPHERES, 0, 1, -15, 0.5F, 0, 0, 0.4F, 0.3F, 1, 1);
		test->requestRender(RenderTypes::POINT_SPHERES, -1, 0, -15, 0.5F, 0, 0, 0.3F, 0.6F, 0.25F, 1);
		test->endRenderRequests();
		test->offsetViewerPos(0, 0, -0.01F);
		test->onFixedUpdate(0.1F);
		test->onUpdateAndDraw(1.0F);
	}
	test->close();
	delete test;
	return 0;
}