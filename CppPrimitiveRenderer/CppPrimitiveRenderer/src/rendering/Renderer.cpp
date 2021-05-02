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
        glfwDestroyWindow(result);
        glfwTerminate();
        return nullptr;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(result);
    /*Initialize glew for use of extention OpenGL Methods*/
    GLenum r = glewInit();
    if (r != GLEW_OK)
    {
        logger->errorPrint2("could not initialize glew!. Error msg: ",(const char*)glewGetErrorString(r));
        glfwDestroyWindow(result);
        glfwTerminate();
        return nullptr;
    }
   logger->notify2("GLEW initialized with OpenGL Version:", glfwGetVersionString());
   hasInitialized = true; 
   return result;
}

void Renderer::beginRenderRequests()
{
    for (std::unordered_map<int, Batch>::iterator i = batches.begin(); i != batches.end(); i++)
    {
        i->second.reset();
    }
}

void Renderer::endRenderRequests()
{
    //remove any batches which were not used since the last update 
    for (std::unordered_map<int, Batch>::iterator i = batches.begin(); i != batches.end();)
    {
        if (!i->second.hasBeenUsedSinceLastUpdate())
        {
            i->second.deleteBatch();
            batches.erase(i);
            continue;
        }
        i++;
    }
}

void Renderer::drawAll()
{
    /* Render here */

    glClear(GL_COLOR_BUFFER_BIT);
    for (std::unordered_map<int, Batch>::iterator i = batches.begin(); i != batches.end(); i++)
    {
        i->second.drawBatch();
    }
}

void Renderer::close()
{
    if (!hasInitialized)return;
    logger->notify("un-initializing rendering...");
    for (std::unordered_map<int, Batch>::iterator i = batches.begin(); i != batches.end(); i++)
    {
        i->second.deleteBatch();
    }
    glfwTerminate();
}
