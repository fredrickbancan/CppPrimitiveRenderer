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
		test->requestRender(RenderTypes::POINT_SPHERES, 0, 0, -10, 10, 10, 10, 1, 1, 1, 1);
		test->endRenderRequests();
		test->onFixedUpdate(0.1F);
		test->onUpdateAndDraw(1.0F);
	}
	test->close();
	delete test;
	return 0;
}