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
/*
Board::Board(std::vector<std::vector<int>> inputarray, unsigned int NumRows, unsigned int NumCollums) {
    glGenBuffers(inputarray.size(), &vbs);
    glGenBuffers(inputarray.size(), &ibo);
    
    for (unsigned int i = 0; i < inputarray.size(); ++i) {
        float vertecies[8];
        unsigned int indcies[6] = {0,1,2,0,1,3};


        genBoardVertexBuffer(inputarray[i][0],inputarray[i][1],NumRows, NumCollums, vertecies);
        



        glBindBuffer(GL_ARRAY_BUFFER, vbs[i]);
        glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), vertecies, GL_STATIC_DRAW);



        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, &ibo[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indcies, GL_STATIC_DRAW);


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
*/
/*
void Board::DrawBoard(std::vector<std::vector<int>> inputarray, unsigned int NumRows, unsigned int NumCollums)
{
    float* vertexbuffers = new float[inputarray.size()*8];
    unsigned int* indexbuffers = new unsigned int[inputarray.size()];

    genBoardVertexBuffer(inputarray, NumRows, NumCollums,vertexbuffers);


    
    for (unsigned int i = 0; i < inputarray.size(); ++i) {
        unsigned int indcies[6] = { 0,1,2,0,1,3 };


        glBindBuffer(GL_ARRAY_BUFFER, vbs);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(float), vertex);

        glDeleteBuffers(1, &ibo);
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indcies,GL_STATIC_DRAW);


        glDrawArrays(GL_TRIANGLES, 6, GL_UNSIGNED_INT);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
*/

void Board::genBoardVertexBuffer(int Row,int Collum,unsigned int NumRows,unsigned int NumCollums, float OutputArray[8])
{
        OutputArray[0]=(static_cast<float>(Row) / (NumCollums));
        OutputArray[1]=(static_cast<float>(Collum+1) / (NumRows));
        OutputArray[2]=(static_cast<float>(Row + 1) / (NumCollums));
        OutputArray[3]=(static_cast<float>(Collum) / (NumRows));
        OutputArray[4]=(static_cast<float>(Row + 1) / (NumCollums));
        OutputArray[5]=(static_cast<float>(Collum+ 1) / (NumRows));
        OutputArray[6]=(static_cast<float>(Row) / (NumCollums));
        OutputArray[7]=(static_cast<float>(Collum) / (NumRows));
}
