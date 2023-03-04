#include "Input.h"
#include "globals.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    xoffset *= 50;
    yoffset *= 50;
    gameX += yoffset;
    gameY += yoffset * RATIO;
    Xoffset += -yoffset / 2;
    Yoffset += (-yoffset * RATIO) / 2;
}