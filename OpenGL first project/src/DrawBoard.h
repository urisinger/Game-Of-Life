#pragma once

#include <vector>
#include "IndexBuffer.h"
#include "vertexbuffer.h"

static void GLclearerrors();
static void GLCheckErrros();

class Board
{
private:
	void genBoardVertexBuffer(int Row, int Collum, unsigned int NumRows, unsigned int NumCollums, float OutputArray[8]);
public:
	unsigned int vbs;
	unsigned int ibo;
	Board(std::vector<std::vector<int>> inputarray, unsigned int NumRows, unsigned int NumCollums);
	void DrawBoard(std::vector<std::vector<int>> inputarray, unsigned int NumRows, unsigned int NumCollums);
};