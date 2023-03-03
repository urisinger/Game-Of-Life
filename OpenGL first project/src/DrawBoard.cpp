/*#include "DrawBoard.h"

#include <iostream>


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

Board::Board(){

    float pos[8];

    VertexBuffer vb(pos, 4 * 2 * sizeof(float));
    IndexBuffer ib(indexs, 6, 1);
}


void Board::draw(std::vector<cell> inputarray)
{
    float pos[8];
    for (int i = 0; i < inputarray.size(); ++i) {

        genBoardVertexBuffer(inputarray[i].x, inputarray[i].y, pos);
        vb.AddData(pos, 4 * 2 * sizeof(float));
        ib.Bind();


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        ib.UnBind();
    }
}


void Board::genBoardVertexBuffer(int Row, int Collum,  float OutputArray[8])
{
    OutputArray[0] = 2 * (static_cast<float>(Row - Xoffset) / (gameX)) - 1;
    OutputArray[1] = 2 * (static_cast<float>(Collum - 1 - Yoffset) / (gameY)) - 1;
    OutputArray[2] = 2 * (static_cast<float>(Row - 1 - Xoffset) / (gameX)) - 1;
    OutputArray[3] = 2 * (static_cast<float>(Collum - Yoffset) / (gameY)) - 1;
    OutputArray[4] = 2 * (static_cast<float>(Row - 1 - Xoffset) / (gameX)) - 1;
    OutputArray[5] = 2 * (static_cast<float>(Collum - 1 - Yoffset) / (gameY)) - 1;
    OutputArray[6] = 2 * (static_cast<float>(Row - Xoffset) / (gameX)) - 1;
    OutputArray[7] = 2 * (static_cast<float>(Collum - Yoffset) / (gameY)) - 1;
}*/