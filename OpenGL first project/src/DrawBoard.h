#pragma once

#include <vector>
#include "IndexBuffer.h"
#include "vertexbuffer.h"

static void GLclearerrors();
static void GLCheckErrros();

class Board
{
private:
	std::vector<std::vector<float>> genBoardVertexBuffer(std::vector<std::vector<int>> inputarray, unsigned int NumRows, unsigned int NumCollums);
public:
	std::vector<unsigned int> vbs;
	std::vector<unsigned int> ibo;
	Board(std::vector<std::vector<int>> inputarray, unsigned int NumRows, unsigned int NumCollums);
};