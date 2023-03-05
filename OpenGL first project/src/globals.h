#pragma once

#include "GameOfLife.h"

#define RATIO  screen_y/screen_x
#define MOUSETOTILE_X gameX * ((xpos / (screen_x))) + 1*(gameX * ((xpos / (screen_x)))+Xoffset >= 0)+Xoffset
#define MOUSETOTILE_Y -gameY * (((ypos) / (screen_y))-1)+1*(-gameY * (((ypos) / (screen_y))-1)+Yoffset>=0)+Yoffset

extern Game Board;

extern vector <bool> brush;
extern unsigned int screen_y;
extern unsigned int screen_x;
extern double gameX;
extern double gameY;
extern double Xoffset;
extern double Yoffset;

extern int brushsizex;
extern int brushsizey;


extern int leftprevtile_X;
extern int leftprevtile_Y;

extern int rightprevtile_X;
extern int rightprevtile_Y;

extern int rightshiftprevtile_X;
extern int rightshiftprevtile_Y;

extern bool rightmouse;
extern bool leftmouse;
extern bool shiftpressed;
extern double xpos, ypos;