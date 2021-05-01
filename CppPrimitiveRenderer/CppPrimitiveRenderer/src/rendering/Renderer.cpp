#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "../Logger.h"
Renderer::Renderer()
{
    logger = new Logger();
}

Renderer::~Renderer()
{
    delete logger;
}

GLFWwindow* Renderer::init(int windowWidth, int windowHeight, const char* title)
{
	GLFWwindow* result = nullptr;
    /* Initialize the library */
    if (!glfwInit())
    {
        logger->errorPrint("could not initialize glfw!");
        return nullptr;
    }
    /* Create a windowed mode window and its OpenGL context */
    result = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
    if (!result)
    {
        logger->errorPrint("could not initialize glfw window!");
        glfwTerminate();
        return nullptr;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(result);
    /*Initialize glew for use of extention OpenGL Methods*/
    GLenum r = glewInit();
    if (r != GLEW_OK)
    {
        logger->errorPrint2("could not initialize glew!. Error msg: ",glewGetErrorString(r));
        glfwTerminate();
        return nullptr;
    }
   logger->notify2("GLEW initialized with OpenGL Version:", glfwGetVersionString());
   hasInitialized = true;
}

void Renderer::beginRenderRequests()
{
}

void Renderer::endRenderRequests()
{
}

void Renderer::drawAll()
{
}

void Renderer::close()
{
    if (!hasInitialized)return;
    logger->notify("un-initializing rendering...");
    glfwTerminate();
}
