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
#define RATIO  Y_SIZE/X_SIZE
#define MOUSETOTILE_X gameX * ((xpos / (X_SIZE))) + 1*(2*xpos>=X_SIZE) +Xoffset
#define MOUSETOTILE_Y -gameY * (((ypos) / (Y_SIZE))-1)+1*(2*ypos<Y_SIZE)+Yoffset
float gameX = 100;
float gameY = gameX*RATIO;
float Xoffset = -gameX/2;
float Yoffset = -gameY/2;

float currenttime = 0.0f;
float prevtime = 0.0f;
float timediff;
unsigned int counter = 0;
float currentfps = 0;

double leftprevtile_X = 0;
double leftprevtile_Y = 0;

double rightprevtile_X = 0;
double rightprevtile_Y = 0;

int timecounter = 0;


bool rightmouse=false;



void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    xoffset *= 50;
    yoffset *= 50;
    gameX += yoffset;
    gameY += yoffset* RATIO;
    Xoffset += -yoffset / 2;
    Yoffset += (-yoffset * RATIO) / 2;
    cout << gameX << endl;
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

    glfwSetScrollCallback(window, scroll_callback);
    Game Board(1);
    std::vector<float> vertcies;

    vector<unsigned int> indexs;


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
    unsigned int vb;
    glCreateBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * 0 * sizeof(float), &vertcies[0], GL_STATIC_DRAW);
    glEnableVertexArrayAttrib(vb, 0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glEnableVertexAttribArray(0);

    //create and save index buffer on gpu
    unsigned int ib;

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        glUseProgram(shader);

        glUniform4f(location, 1.0f, 1.0f, 1.0f, 1.0f);

        glBindVertexArray(vao);
        //draw board

        vertcies.resize(8*Board.currentBoard.size());
        indexs.resize(6*Board.currentBoard.size());
        unsigned int counter = 0;
       for (const auto& cell : Board.currentBoard) {
            //generates data for buffer
           int Row = cell.first;
           int Collum = cell.second;
           vertcies[8*counter]=(2 * (static_cast<float>(Row - Xoffset) / (gameX)) - 1);
           vertcies[8*counter+1]=(2 * (static_cast<float>(Collum - 1 - Yoffset) / (gameY)) - 1);
           vertcies[8*counter+2]=(2 * (static_cast<float>(Row - 1 - Xoffset) / (gameX)) - 1);
           vertcies[8*counter+3]=(2 * (static_cast<float>(Collum - Yoffset) / (gameY)) - 1);
           vertcies[8*counter+4]=(2 * (static_cast<float>(Row - 1 - Xoffset) / (gameX)) - 1);
           vertcies[8*counter+5]=(2 * (static_cast<float>(Collum - 1 - Yoffset) / (gameY)) - 1);
           vertcies[8*counter+6]=(2 * (static_cast<float>(Row - Xoffset) / (gameX)) - 1);
           vertcies[8*counter+7]=(2 * (static_cast<float>(Collum - Yoffset) / (gameY)) - 1);

           indexs[6*counter]=(4*counter);
           indexs[6*counter+1]=(4*counter + 1);
           indexs[6*counter+2]=(4*counter+2);
           indexs[6*counter+3]=(4*counter);
           indexs[6*counter+4]=(4*counter + 1);
           indexs[6*counter+5]=(4*counter + 3);
           counter++;
        }
       
       glBindVertexArray(vao);
       glBindBuffer(GL_ARRAY_BUFFER, vb);
       glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertcies.size(), vertcies.data(), GL_DYNAMIC_DRAW);

       glCreateBuffers(1, &ib);
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
       glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexs.size(), &indexs[0], GL_STATIC_DRAW);


       glDrawElements(GL_TRIANGLES, 6*counter, GL_UNSIGNED_INT, nullptr);

       vertcies.clear();
       indexs.clear();

        //fps and updateboard
        currenttime = glfwGetTime();
        timediff = currenttime - prevtime;
        timecounter++;
        if (timediff >= 1 / 10.0f) {
            currentfps = timecounter / timediff;
            prevtime = currenttime;
            glfwSetWindowTitle(window, std::to_string(currentfps).c_str());
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                Board.UpdateBoard();
            }
            timecounter = 0;

        }



        //mouse calls
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int row = MOUSETOTILE_X, collum = MOUSETOTILE_Y;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            //check if tile was already swapped
            if (!(leftprevtile_X == row && leftprevtile_Y == collum)) {
                //swap tile
                Board.ChangeTile(row, collum);
                leftprevtile_X = row, leftprevtile_Y = collum;
            }
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            if (rightmouse == false) {
                rightprevtile_X = row;
                rightprevtile_Y = collum;
                rightmouse = true;
            }
            //upper limit
            float mousespeedX = 10 * (rightprevtile_X - row) / currentfps > gameX/currentfps ? gameX / currentfps : 10 * (rightprevtile_X - row) / currentfps;
            float mousespeedY = 10 * (rightprevtile_Y - collum) / currentfps > gameX / currentfps ? gameX / currentfps : 10 * (rightprevtile_Y - collum) / currentfps;

            //lower limit 
            mousespeedX = mousespeedX < -gameX / currentfps ? -gameX / currentfps : mousespeedX;
            mousespeedY = mousespeedY < -gameX / currentfps ? -gameX / currentfps : mousespeedY;

            Xoffset += mousespeedX;
            Yoffset += mousespeedY;
        }
        else {
            rightmouse = false;
        }


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    glDeleteProgram(shader);
        glfwTerminate();
        return 0;
    }