#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>


unsigned int CreateShader();
unsigned int compileshader(unsigned int type, const std::string& source);
std::string openshader(const char* filePath);