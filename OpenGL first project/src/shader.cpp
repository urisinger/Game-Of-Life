#include "shader.h"

std::string openshader(const char* filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

unsigned int compileshader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* messge = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, messge);
        std::cout << "failt to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << messge << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


unsigned int CreateShader()
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileshader(GL_VERTEX_SHADER, openshader("res/shader/vertex.shader"));
    unsigned int fs = compileshader(GL_FRAGMENT_SHADER, openshader("res/shader/fragment.shader"));

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
