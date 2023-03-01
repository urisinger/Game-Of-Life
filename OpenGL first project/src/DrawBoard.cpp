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

Board::Board(std::vector<std::vector<int>> inputarray, unsigned int NumRows, unsigned int NumCollums) {
    std::vector<std::vector<float>> vertexbuffers;
    unsigned int* indexbuffers = new unsigned int[inputarray.size()];

    vertexbuffers = genBoardVertexBuffer(inputarray, NumRows, NumCollums);


    vbs.reserve(vertexbuffers.size());
    vbs.resize(vertexbuffers.size());
    ibo.reserve(vertexbuffers.size());
    ibo.resize(vertexbuffers.size());
    for (unsigned int i = 0; i < vertexbuffers.size(); ++i) {
        unsigned int indcies[6] = {i,i + 1,i + 2,i,i + 1,i + 3 };
        std::vector<float>* a = &vertexbuffers[i];


        glGenBuffers(1, &vbs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vbs[i]);
        glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), a, GL_STATIC_DRAW);


        glGenBuffers(0, &ibo[i]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indcies, GL_STATIC_DRAW);


        glDrawArrays(GL_TRIANGLES, 6, GL_UNSIGNED_INT);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}



std::vector<std::vector<float>> Board::genBoardVertexBuffer(std::vector<std::vector<int>> inputarray,unsigned int NumRows,unsigned int NumCollums)
{
    std::vector<std::vector<float>> OutputArray;
    for (int i = 0; i < inputarray.size(); ++i) {
        std::vector<float> v1;
        OutputArray.push_back(v1);
        OutputArray[i].push_back(static_cast<float>(inputarray[i][0]) / (NumCollums));
        OutputArray[i].push_back(static_cast<float>(inputarray[i][1]+1) / (NumRows));
        OutputArray[i].push_back(static_cast<float>(inputarray[i][0] + 1) / (NumCollums));
        OutputArray[i].push_back(static_cast<float>(inputarray[i][1]) / (NumRows));
        OutputArray[i].push_back(static_cast<float>(inputarray[i][0] + 1) / (NumCollums));
        OutputArray[i].push_back(static_cast<float>(inputarray[i][1] + 1) / (NumRows));
        OutputArray[i].push_back(static_cast<float>(inputarray[i][0]) / (NumCollums));
        OutputArray[i].push_back(static_cast<float>(inputarray[i][1]) / (NumRows));
    }
    return OutputArray;
}
