#include "DrawBoard.h"

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
Board::Board(unsigned int RowCount, unsigned int CollumCount) {
    
}

void Board::genBoardVertexBuffer(unsigned int RowCount, unsigned int CollumCount, float OutputArray[])
{
    for (int i = 0; i <= RowCount;i++) {
        for (int j = 0; j <= CollumCount;j++) {
            OutputArray[2 * (i * (CollumCount+1) + j)] = 2* (j / static_cast<float>(CollumCount)) - 1.0f;
            OutputArray[2 * (i * (CollumCount+1) + j)+1] = 2* (i / static_cast<float>(RowCount)) - 1.0f;
        }
    }
}
