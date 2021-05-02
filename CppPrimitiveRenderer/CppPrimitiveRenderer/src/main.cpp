#include "GraphicsWindow.h"
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
		test->endRenderRequests();
		test->drawAll();
	}
	test->close();
	delete test;
	return 0;
}