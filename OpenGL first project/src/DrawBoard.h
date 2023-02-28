#pragma once


#include <vector>
#include "IndexBuffer.h"
#include "vertexbuffer.h"

static void GLclearerrors();
static void GLCheckErrros();

class Board
{
public:
	Board(unsigned int RowCount, unsigned int CollumCount);

	void genBoardVertexBuffer(unsigned int RowCount,unsigned int CollumCount, float OutputArray[]);
	void genBoardIndexBuffer(std::vector<std::vector<bool>> inputBoard, void* location);
};