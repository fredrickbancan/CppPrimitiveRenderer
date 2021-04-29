#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    cout << "GLFW initialized." << endl;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
   
    /*Initialize glew for use of extention OpenGL Methods*/
    GLenum r = glewInit();
    if (r != GLEW_OK)
    {
        cout << "Error: "<< glewGetErrorString(r) << endl;
        return -1;
    }

    cout << "GLEW initialized." << endl;

    cout << "OpenGL Version: " << glfwGetVersionString() << endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*Making triangle with immediate mode*/
        glBegin(GL_TRIANGLES);
        glColor3f(1.0F, 0.0F, 0.0F);
        glVertex2f(0.0F, 0.5F);
        glColor3f(0.0F, 1.0F, 0.0F);
        glVertex2f(-0.5F, -0.5F);
        glColor3f(0.0F, 0.0F, 1.0F);
        glVertex2f(0.5F, -0.5F);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}