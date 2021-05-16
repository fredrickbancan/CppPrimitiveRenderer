#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "../Logger.h"
#include "Batch.h"
#include "BatchUtil.h"
#include "Camera.h"
using namespace std;
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

   BatchUtil::loadAllShaders(logger);

   return result;
}

void Renderer::beginRenderRequests()
{ 
    //remove any batches which were not used since the last update 
    for (std::unordered_map<int, Batch*>::iterator i = batches.begin(); i != batches.end();)
    {
        if (!i->second->hasBeenUsedSinceLastUpdate())
        {
            i->second->deleteBatch();
            delete i->second;
            batches.erase(i);
            continue;
        }
        i++;
    }

    //prepare all batches to accept render requests
    for (std::unordered_map<int, Batch*>::iterator i = batches.begin(); i != batches.end(); i++)
    {
        i->second->reset();
    }
}

void Renderer::requestRender(int renderType, glm::vec3 pos, glm::vec3 size, glm::vec4 color)
{
    std::unordered_map<int, Batch*>::iterator match;
    if ((match = batches.find(renderType)) != batches.end())
    {
        //add to match
        match->second->addToBatch(pos, size, color);
        return;
    }
    //add new batch
    Batch* b = BatchUtil::makeBatch(renderType);
    b->addToBatch(pos, size, color);
    batches[renderType] = b;
}

void Renderer::requestRenderLerp(int renderType, glm::vec3 pos, glm::vec3 size, glm::vec4 color, glm::vec3 prevPos, glm::vec3 prevSize, glm::vec4 prevColor)
{
    std::unordered_map<int, Batch*>::iterator match;
    if ((match = batches.find(renderType)) != batches.end())
    {
        //add to match
        match->second->addToBatchLerp(pos, size, color, prevPos, prevSize, prevColor);
        return;
    }
    //add new batch
    Batch* b = BatchUtil::makeBatch(renderType);
    b->addToBatchLerp(pos, size, color, prevPos, prevSize, prevColor);
    batches[renderType] = b;
    delete b;
}

void Renderer::endRenderRequests()
{
    //prepare all batches for rendering
    for (std::unordered_map<int, Batch*>::iterator i = batches.begin(); i != batches.end(); i++)
    {
        i->second->updateBuffers();
    }
}

void Renderer::drawAll(Camera* viewer, float lerpFactor)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (std::unordered_map<int, Batch*>::iterator i = batches.begin(); i != batches.end(); i++)
    {
        i->second->updateUniforms(viewer->getProjectionMatrix(), viewer->getViewMatrix(), lerpFactor);
        i->second->drawBatch();
    }
}

void Renderer::swapAndPoll(GLFWwindow* windowHandle)
{
    /* Swap front and back buffers */
    glfwSwapBuffers(windowHandle);
    /* Poll for and process events */
    glfwPollEvents();
}

bool Renderer::shouldWindowClose(GLFWwindow* windowHandle)
{
    return glfwWindowShouldClose(windowHandle) > 0;
}

void Renderer::destroyWindow(GLFWwindow* windowHandle)
{
    glfwDestroyWindow(windowHandle);
}

void Renderer::close()
{
    if (!hasInitialized)return;
    logger->notify("un-initializing rendering...");

    BatchUtil::deleteAllShaders();

    for (std::unordered_map<int, Batch*>::iterator i = batches.begin(); i != batches.end(); i++)
    {
        i->second->deleteBatch();
        delete i->second;
    }
    glfwTerminate();
}
