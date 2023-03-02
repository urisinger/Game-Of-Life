#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>

//#include "DrawBoard.h"
#include "GameOfLife.h"
#include "vertexbuffer.h"
#include "IndexBuffer.h"
#include "shader.h"

#define X_SIZE 1920
#define Y_SIZE 1080
#define MOUSETOTILE gameX*(((2*xpos) / (X_SIZE))-1)-1*((2 * xpos > X_SIZE) * 2 - 1), -gameY*(((2*ypos)/(Y_SIZE))-1)-1*((2*ypos>Y_SIZE)*2-1)
float gameX = 100;
float gameY = 100;
Game test(1);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        test.ChangeTile(MOUSETOTILE);
    //    test.PrintBoard();
    }

}


static void GLclearerrors()
{
    while (glGetError());
}

static void GLCheckErrros()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[opengl error](" << error << ")" << std::endl;
    }
}



void genBoardVertexBuffer(int Row, int Collum, float OutputArray[8])
{
    OutputArray[0] = (static_cast<float>(Row) / (gameX));
    OutputArray[1] = (static_cast<float>(Collum - 1) / (gameY));
    OutputArray[2] = (static_cast<float>(Row - 1) / (gameX));
    OutputArray[3] = (static_cast<float>(Collum) / (gameY));
    OutputArray[4] = (static_cast<float>(Row - 1) / (gameX));
    OutputArray[5] = (static_cast<float>(Collum -1) / (gameY));
    OutputArray[6] = (static_cast<float>(Row) / (gameX));
    OutputArray[7] = (static_cast<float>(Collum) / (gameY));
}


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
    window = glfwCreateWindow(X_SIZE, Y_SIZE, "Game of life", NULL, NULL);
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

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    float pos[8];

    unsigned int indexs[6] =
    {
        0,1,2,
        0,1,3
    };


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
    VertexBuffer vb(pos, 4 * 2 * sizeof(float));


    glEnableVertexAttribArray(0);

    //create and save index buffer on gpu
    IndexBuffer ib(indexs, 6, 1);

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    float currenttime = 0.0f;
    float prevtime = 0.0f;
    float timediff;
    unsigned int counter = 0;
    float currentfps = 0;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        float pos[8];

        glUseProgram(shader);

        glUniform4f(location, 1.0f, 1.0f, 1.0f, 1.0f);

        glBindVertexArray(vao);

        for (int i = 0; i < test.Board.size(); ++i) {
            genBoardVertexBuffer(test.Board[i][0], test.Board[i][1], pos);
            vb.AddData(pos, 4 * 2 * sizeof(float));
            ib.Bind();


            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            ib.UnBind();
        }




        //fps
        currenttime = glfwGetTime();
        timediff = currenttime - prevtime;
        counter++;
        if (timediff >= 1 / 3.0f) {
            //std::cout << counter / timediff << std::endl;
            currentfps = counter / timediff;
            prevtime = currenttime;
            counter = 0;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS) {
                test.UpdateBoard();
            }
            std::cout << currentfps << std::endl;
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}