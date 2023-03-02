#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>


#include "GameOfLife.h"
#include "vertexbuffer.h"
#include "IndexBuffer.h"
#include "shader.h"

#define X_SIZE 1920
#define Y_SIZE 1080
#define MOUSETOTILE gameX * ((xpos / (X_SIZE))) +1 +Xoffset, -gameY * (((ypos) / (Y_SIZE))-1)+1+Yoffset
float gameX = 10;
float gameY = 10;
float Xoffset = -gameX/2;
float Yoffset = -gameY/2;
Game test(1);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        test.ChangeTile(MOUSETOTILE);
    }

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    gameX += yoffset;
    gameY += yoffset;
    Xoffset = -gameX / 2;
    Yoffset = -gameY / 2;
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
    OutputArray[0] = 2*(static_cast<float>(Row-Xoffset) / (gameX))-1;
    OutputArray[1] = 2*(static_cast<float>(Collum - 1-Yoffset) / (gameY))-1;
    OutputArray[2] = 2*(static_cast<float>(Row - 1- Xoffset) / (gameX))-1;
    OutputArray[3] = 2*(static_cast<float>(Collum- Yoffset) / (gameY))-1;
    OutputArray[4] = 2*(static_cast<float>(Row - 1- Xoffset) / (gameX))-1;
    OutputArray[5] = 2*(static_cast<float>(Collum -1- Yoffset) / (gameY))-1;
    OutputArray[6] = 2*(static_cast<float>(Row- Xoffset) / (gameX))-1;
    OutputArray[7] = 2*(static_cast<float>(Collum- Yoffset) / (gameY))-1;
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

    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK) {
        std::cout << "error!" << std::endl;
    }

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
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

        for (int i = 0; i < test.CurrentBoard.size(); ++i) {
            genBoardVertexBuffer(test.CurrentBoard[i].x, test.CurrentBoard[i].y, pos);
            vb.AddData(pos, 4 * 2 * sizeof(float));
            ib.Bind();


            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            ib.UnBind();
        }




        //fps
        currenttime = glfwGetTime();
        timediff = currenttime - prevtime;
        counter++;
        if (timediff >= 1 / 10.0f) {
            //std::cout << counter / timediff << std::endl;
            currentfps = counter / timediff;
            prevtime = currenttime;
            counter = 0;
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS) {
                test.UpdateBoard();
            }
            glfwSetWindowTitle(window, std::to_string(currentfps).c_str());
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}