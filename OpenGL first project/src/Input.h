#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void mosuecalls(double currentfps);
void paintbrush(int row, int collum);

void coppybrush();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);