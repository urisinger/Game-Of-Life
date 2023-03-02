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

void genBoardVertexBuffer(int Row, int Collum, unsigned int NumRows, unsigned int NumCollums, float OutputArray[8])
{
    OutputArray[0] = (static_cast<float>(Row) / (NumCollums));
    OutputArray[1] = (static_cast<float>(Collum + 1) / (NumRows));
    OutputArray[2] = (static_cast<float>(Row + 1) / (NumCollums));
    OutputArray[3] = (static_cast<float>(Collum) / (NumRows));
    OutputArray[4] = (static_cast<float>(Row + 1) / (NumCollums));
    OutputArray[5] = (static_cast<float>(Collum + 1) / (NumRows));
    OutputArray[6] = (static_cast<float>(Row) / (NumCollums));
    OutputArray[7] = (static_cast<float>(Collum) / (NumRows));
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

    float width = 0.5f;
    float height = 0.1f;
    float Xoffset = 0.0f;
    float Yoffset = 0.0f;

    float speed = 1.0f / 60.0f;


    float pos[8] =
    {
       -width + Xoffset,-height + Yoffset,
        width + Yoffset,height + Yoffset,
       -width + Xoffset,height + Yoffset,
        width + Xoffset,-height + Yoffset,

    };

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

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

    Game test(1);
    test.Board.push_back({ 1,1 });
    test.Board.push_back({ 1,3 });
    test.Board.push_back({ 4,3 });
    for (int i = 0; i < test.Board.size(); ++i) {
        std::cout << test.Board[i][0] << ":" << test.Board[i][1] << std::endl;
    }
    test.UpdateBoard();
    for (int i = 0; i < test.Board.size(); ++i) {
        std::cout << test.Board[i][0] << ":" << test.Board[i][1] << std::endl;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        Xoffset = 0.0f;
        Yoffset = 0.0f;
        float pos[8] = {
           -width + Xoffset,-height + Yoffset,
            width + Xoffset,height + Yoffset,
           -width + Xoffset,height + Yoffset,
            width + Xoffset,-height + Yoffset,
        };

        glUseProgram(shader);

        glUniform4f(location, 0.8f, 0.3f, 0.02f, 1.0f);

        glBindVertexArray(vao);

        vb.AddData(pos, 4 * 2 * sizeof(float));
        ib.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        ib.UnBind();
        Xoffset = 0.3f;
        Yoffset = 0.1f;
        float pos2[8] = {
   -width + Xoffset,-height + Yoffset,
    width + Xoffset,height + Yoffset,
   -width + Xoffset,height + Yoffset,
    width + Xoffset,-height + Yoffset,
        };
        vb.AddData(pos2, 4 * 2 * sizeof(float));
        ib.Bind();


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);

        //fps
        currenttime = glfwGetTime();
        timediff = currenttime - prevtime;
        counter++;
        if (timediff >= 1 / 30.0f) {
            //std::cout << counter / timediff << std::endl;
            currentfps = counter / timediff;
            prevtime = currenttime;
            counter = 0;
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}