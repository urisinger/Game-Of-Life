#pragma once

#define RATIO  screen_y/screen_x
#define MOUSETOTILE_X gameX * ((xpos / (screen_x))) + 1*(gameX * ((xpos / (screen_x)))+Xoffset >= 0)+Xoffset
#define MOUSETOTILE_Y -gameY * (((ypos) / (screen_y))-1)+1*(-gameY * (((ypos) / (screen_y))-1)+Yoffset>=0)+Yoffset
extern unsigned int screen_y = 1080;
extern unsigned int screen_x = 1920;
extern double gameX;
extern double gameY;
extern double Xoffset;
extern double Yoffset;
