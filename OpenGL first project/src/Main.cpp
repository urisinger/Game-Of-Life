#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>


#include "GameOfLife.h"
#include "vertexbuffer.h"
#include "IndexBuffer.h"
#include "shader.h"

#include "Input.h"

#include "globals.h"



unsigned int screen_y = 1080;
unsigned int screen_x = 1920;
double gameX = 100;
double gameY = gameX * RATIO;
double Xoffset = -gameX / 2;
double Yoffset = -gameY / 2;

int leftprevtile_X = 0;
int leftprevtile_Y = 0;

int rightprevtile_X = 0;
int rightprevtile_Y = 0;

int rightshiftprevtile_Y=0;
int rightshiftprevtile_X=0;
double xpos, ypos;

vector <bool> brush={1};
int brushsizex=1;
int brushsizey=1;

bool shiftpressed=false;
bool leftmouse = false;
bool rightmouse = false;

Game Board(1);




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
    window = glfwCreateWindow(screen_x, screen_y, "Game of life", NULL, NULL);
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



    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);



    vector<float> vertcies;

    vector<unsigned int> indecies;



    double currenttime = 0.0f;
    double prevtime = 0.0f;
    double timediff;
    int timecounter = 0;
    int currentfps = 0;


    unsigned int counter = 0;

    // gen vertex array 
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //setup shader

    //gen vertex buffer
    VertexBuffer vb(1);


    //create and save index buffer on gpu
    IndexBuffer ib(1);

    Shader sh("res/shader/vertex.shader", "res/shader/fragment.shader");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    sh.unbind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        sh.bind();

        glBindVertexArray(vao);
        //draw board

        //generates data for buffer

        vertcies.resize(8*Board.currentBoard.size());
        indecies.resize(6*Board.currentBoard.size());
        unsigned int counter = 0;
       for (const auto& cell : Board.currentBoard) {

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

           indecies[6*counter]=(4*counter);
           indecies[6*counter+1]=(4*counter + 1);
           indecies[6*counter+2]=(4*counter+2);
           indecies[6*counter+3]=(4*counter);
           indecies[6*counter+4]=(4*counter + 1);
           indecies[6*counter+5]=(4*counter + 3);
           counter++;
        }
       

       vb.AddData(vertcies.data(),sizeof(float) * vertcies.size());
       ib.adddata(indecies.data(), indecies.size());


       glDrawElements(GL_TRIANGLES, 6*counter, GL_UNSIGNED_INT, nullptr);

       vertcies.clear();
       indecies.clear();

        //fps and updateboard
        currenttime = glfwGetTime();
        timediff = currenttime - prevtime;
        timecounter++;
        if (timediff >= 1 /20.0) {
            currentfps = timecounter / timediff;
            prevtime = currenttime;
            glfwSetWindowTitle(window, std::to_string(currentfps).c_str());
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                Board.UpdateBoard();
            }
            timecounter = 0;

        }



        //mouse calls

        glfwGetCursorPos(window, &xpos, &ypos);

        mosuecalls(currentfps);


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        glfwTerminate();
        return 0;
    }