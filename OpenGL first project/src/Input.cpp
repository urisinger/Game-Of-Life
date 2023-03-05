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


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT_SHIFT) {
        if(action == GLFW_PRESS){
            shiftpressed = true;
            if (rightmouse) {
                rightshiftprevtile_X = MOUSETOTILE_X;
                rightshiftprevtile_Y = MOUSETOTILE_Y;
            }

        }
        else if (action == GLFW_RELEASE) {
            shiftpressed = false;
        }
    }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            rightmouse = true;
            if (shiftpressed) {
                rightshiftprevtile_X = MOUSETOTILE_X;
                rightshiftprevtile_Y = MOUSETOTILE_Y;
                return;
            }
            rightprevtile_X = MOUSETOTILE_X;
            rightprevtile_Y = MOUSETOTILE_Y;
            return;
        }
            rightmouse = false;
         brush.clear();
           coppybrush();
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            leftmouse = true;
            return;
        }

        leftmouse = false;

    }
        
}

void mosuecalls(double currentfps) {
    int row = MOUSETOTILE_X, collum = MOUSETOTILE_Y;

    if (leftmouse) {
        //check if tile was already swapped
        if (!(leftprevtile_X == row && leftprevtile_Y == collum)) {
            //swap tile
            paintbrush(row, collum);
            leftprevtile_X = row, leftprevtile_Y = collum;
        }
    }

    if (rightmouse) {
        if (shiftpressed) {
            //upper limit
            double mousespeedX = 10 * (rightprevtile_X - row) / currentfps > gameX / currentfps ? gameX / currentfps : 10 * (rightprevtile_X - row) / currentfps;
            double mousespeedY = 10 * (rightprevtile_Y - collum) / currentfps > gameX / currentfps ? gameX / currentfps : 10 * (rightprevtile_Y - collum) / currentfps;

            //lower limit 
            mousespeedX = mousespeedX < -gameX / currentfps ? -gameX / currentfps : mousespeedX;
            mousespeedY = mousespeedY < -gameX / currentfps ? -gameX / currentfps : mousespeedY;

            Xoffset += mousespeedX;
            Yoffset += mousespeedY;
        }
    }

}

void paintbrush(int row,int collum) {
    for (int i = 0; i < brushsizex; i++) {
        for (int j = 0; j < brushsizey; j++) {
            if (brush[i * brushsizey + j]) {
                Board.currentBoard.emplace(row + i-brushsizex/2, collum + j-brushsizey/2);
            }
        }
    }
}


void coppybrush() {
    brushsizex = abs(rightprevtile_X - (MOUSETOTILE_X));
    brushsizey = abs(rightprevtile_Y- (MOUSETOTILE_Y));

    brush.resize(brushsizex * brushsizey);
    for (int i = 0; i < brushsizex; i++) {
            for (int j = 0; j < brushsizey; j++) {
                brush[i*brushsizey+j]=((Board.currentBoard.find({i*(2*(rightprevtile_X - (MOUSETOTILE_X)>0)-1) + (int)MOUSETOTILE_X, j*(2*(rightprevtile_Y - (MOUSETOTILE_Y) > 0)-1) + (int)MOUSETOTILE_Y}) != Board.currentBoard.end()));
        }
    }
}