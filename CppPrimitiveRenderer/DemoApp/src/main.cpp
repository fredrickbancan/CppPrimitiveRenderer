#include "GraphicsWindow.h"
#include "RenderTypes.h"
#include "Input.h"
#include "InputCodes.h"
#include "Primitive.h"
#include <vector>
#include <ctime>
using namespace std;

/*for randomizing primitive colors*/
float rndFloat()
{
	return (float)rand() / (float)RAND_MAX;
}

int main(void)
{
	/*initializing the graphics window*/
	GraphicsWindow* test = new GraphicsWindow(640, 480, "Demo App!");
	if (!test->init())//if the window does not successfully initialize, close app.
	{
		test->close();
		delete test;
		return -1;
	}

	/*vector for holding and manipulating generated primitives*/
	vector<Primitive> primitives;

	/*initializing input object for user input*/
	Input* input = new Input(test->getGLFWWindowHandle());

	/*Setting up initial conditions*/
	input->setGrabMouse(true);
	input->setMouseVisible(false);
	test->setBackgroundColor(0.1F,0.5F,0.6F);
	float moveSpeed = 0.1F;
	float mouseSensitivity = 0.05F;
	bool paused = false;
	bool pauseButtonAlreadyDown = false;
	srand(time(0));

	/*adding a few initial primitives*/
	primitives.push_back({ RenderTypes::POINT_SPHERES, 0, 0, -15, 0.5F, 0, 0, 0.3F, 0.5F, 1, 1 });
	primitives.push_back({ RenderTypes::POINT_SPHERES, 0, 0.5, -15, 0.5F, 0, 0, 0.4F, 0.3F, 1, 1 });
	primitives.push_back({ RenderTypes::POINT_SPHERES, -0.5, 0, -15, 0.5F, 0, 0, 0.3F, 0.6F, 0.25F, 1 });
	primitives.push_back({ RenderTypes::CUBES, -1.5, 0, 15, 1, 1, 0.5, 0.4F, 0.2F, 0.9F, 1 });
	primitives.push_back({ RenderTypes::CUBES, 3.5, 0, 15, 1,4, 1, 0.9F, 1.0F, 0.8F, 1 });
	primitives.push_back({ RenderTypes::CUBES, 0, -6, 15,10, 0.5, 10, 1.0F, 0.2F, 0.3F, 1 });

	/*Game/Application Logic Loop. Will run untill window closes or user presses escape.*/
	while (!test->isWindowBeingClosed() && !input->isKeyDown(INPUT_KEY_ESCAPE))
	{

		/*request renders for all stored primitives.*/
		test->beginRenderRequests();
		for (vector<Primitive>::iterator i = primitives.begin(); i != primitives.end(); i++)
		{
			const Primitive& var = *i;
			test->requestRender(var.type, var.posX, var.posY, var.posZ, var.sizeX, var.sizeY, var.sizeZ, var.colorR, var.colorG, var.colorB, var.colorA);
		}
		test->endRenderRequests();

		/*Process user pausing application*/
		bool pauseButtonDown = false;
		if ((pauseButtonDown = input->isKeyDown(INPUT_KEY_E)) && !pauseButtonAlreadyDown)
		{
			paused = !paused;
			pauseButtonAlreadyDown = true;
		}
		else if(!pauseButtonDown)
		{
			pauseButtonAlreadyDown = false;
		}

		/*Grab or release mouse based on if app is paused*/
		input->setGrabMouse(!paused);
		input->setMouseVisible(paused);

		if (!paused)
		{
			/*rotate camera based on mouse movement*/
			double dx, dy;
			input->getMouseDeltas(&dx, &dy);
			test->rotateViewerYaw(dx * mouseSensitivity);
			test->rotateViewerPitch(dy * -mouseSensitivity);

			/*move camerea based on w,a,s,d,space,ctrl presses.*/
			test->moveViewerFowards(moveSpeed * ((int)input->isKeyDown(INPUT_KEY_W) - (int)input->isKeyDown(INPUT_KEY_S)));
			test->strafeViewerRight(moveSpeed * ((int)input->isKeyDown(INPUT_KEY_D) - (int)input->isKeyDown(INPUT_KEY_A)));
			test->moveViewerUpwards(moveSpeed * ((int)input->isKeyDown(INPUT_KEY_SPACE) - (int)input->isKeyDown(INPUT_KEY_LEFT_CONTROL)));

			/*getting position to spawn primitives*/
			float x, y, z, fx, fy, fz;
			test->getViewerPos(&x, &y, &z);
			test->getViewerFrontDirection(&fx, &fy, &fz);

			/*spawn randomized sphere or cube depending on left or right mouse button pressed.*/
			if (input->isMouseButtonDown(INPUT_MOUSE_BUTTON_1))
			{
				primitives.push_back({ RenderTypes::POINT_SPHERES, x + fx, y + fy, z + fz,  0.05F + rndFloat() * 0.45F, 0, 0, rndFloat(),  rndFloat(),  rndFloat(), 1 });
			}
			else if (input->isMouseButtonDown(INPUT_MOUSE_BUTTON_2))
			{
				primitives.push_back({ RenderTypes::CUBES, x + fx, y + fy, z + fz, 1 + rndFloat() * 2, 1 + rndFloat() * 2, 1 + rndFloat() * 2, rndFloat(), rndFloat(),  rndFloat(), 1 });
			}
		}
		/*call update functions for graphics window*/
		test->onFixedUpdate(0.1F);
		input->update();

		/*call rendering and update function*/
		test->onUpdateAndDraw(1.0F);
	}

	/*once leaving game loop, delete everything and close graphics window.*/
	test->close();
	delete test;
	delete input;
	return 0;
}