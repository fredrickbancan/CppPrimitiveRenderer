#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "../Logger.h"
#include "Batch.h"
#include "BatchUtil.h"
#include "Camera.h"
#include <iostream>
using namespace std;

void APIENTRY glErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    if (!(severity != GL_DEBUG_SEVERITY_LOW && severity != GL_DEBUG_SEVERITY_MEDIUM && severity != GL_DEBUG_SEVERITY_HIGH))
    {
        cout << "\n\n\n\n---------------------opengl-message-start------------" << endl;
        cout << "message: " << message << endl;
        cout << "type: ";
        switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            cout << "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            cout << "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            cout << "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            cout << "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            cout << "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_OTHER:
            cout << "OTHER";

            break;
        }
        cout << endl;

        cout << "id: " << id << endl;
        cout << "severity: ";
        switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            cout << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            cout << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            cout << "HIGH";
            break;
        default:
            cout << "NOTIFICATION";
            break;
        }
        cout << endl;
        cout << "---------------------opengl-message-end--------------" << endl;
    }
    if (severity == GL_DEBUG_SEVERITY_HIGH)
    {
        __debugbreak();
    }
}
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

	/*establish error callback*/
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(glErrorCallback, nullptr);

    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_PROGRAM_POINT_SIZE);
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

void Renderer::drawAll(GLFWwindow* windowHandle, Camera* viewer, float lerpFactor)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glm::vec2 prevViewPort = viewPortSize;
    viewPortSize = getViewPortSize(windowHandle);
    if ((viewPortSize.x != prevViewPort.x || viewPortSize.y != prevViewPort.y) && viewPortSize.x + viewPortSize.y > 0)
    {
        glViewport(0, 0, (int)viewPortSize.x, (int)viewPortSize.y);
    }
    for (std::unordered_map<int, Batch*>::iterator i = batches.begin(); i != batches.end(); i++)
    {
        i->second->updateUniforms(viewer->getProjectionMatrix(), viewer->getViewMatrix(), viewPortSize, lerpFactor);
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

glm::vec2 Renderer::getViewPortSize(GLFWwindow* windowHandle)
{
    int x = 0;
    int y = 0;
    glfwGetFramebufferSize(windowHandle, &x, &y);
    return glm::vec2(x,y);
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
