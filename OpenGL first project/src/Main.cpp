#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>

#include "DrawBoard.h"
#include "GameOfLife.h"
#include "vertexbuffer.h"
#include "IndexBuffer.h"
#include "shader.h"



int main(void)
{
    GLFWwindow* window;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "error!" << std::endl;
    }
    


    // gen vertex array 
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //setup shader
    unsigned int shader = CreateShader();
    glUseProgram(shader);


    //setup uniform
    int location = glGetUniformLocation(shader, "u_color");
    _ASSERT(location != -1);

    //gen vertex buffer
   // VertexBuffer vb(pos, 4 * 2 * sizeof(float));


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //create and save index buffer on gpu
   // IndexBuffer ib(indexs, 6,1);

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
        
    double currenttime = 0.0f;
    double prevtime = 0.0f;
    double timediff;
    unsigned int counter = 0;
    float currentfps = 0;

    Game test(1);
    
    test.AddTile(0, 0,test.Board);
    test.AddTile(0, 1, test.Board);
    test.AddTile(0, 2, test.Board);
    test.AddTile(1, 1, test.Board);
    test.AddTile(1, 2, test.Board);
    test.AddTile(1, 3, test.Board);

    Board board(test.Board, 2, 4);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        glUseProgram(shader);

        glUniform4f(location, 0.8f, 0.3f, 0.02f, 1.0f);

        glBindVertexArray(vao);

        Board board(test.Board, 2, 4);



        //fps
        currenttime = glfwGetTime();
        timediff = currenttime - prevtime;
        counter++;
        if (timediff >= 1 / 5.0f) {
            //std::cout << counter / timediff << std::endl;
            currentfps = counter / timediff;
            prevtime = currenttime;
            counter = 0;
            std::cout << currentfps<<std::endl;
        }
        glBindVertexArray(0);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}