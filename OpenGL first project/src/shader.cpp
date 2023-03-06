#include "shader.h"


Shader::Shader(std::string VertexFilePath, std::string FragmentFilePath)
{
    Renderer_ID = glCreateProgram();
    unsigned int vs = compileshader(GL_VERTEX_SHADER, openshader(VertexFilePath));
    unsigned int fs = compileshader(GL_FRAGMENT_SHADER, openshader(FragmentFilePath));

    glAttachShader(Renderer_ID, vs);
    glAttachShader(Renderer_ID, fs);
    glLinkProgram(Renderer_ID);
    glValidateProgram(Renderer_ID);

    glDeleteShader(vs);
    glDeleteShader(fs);


    location = glGetUniformLocation(Renderer_ID, "u_color");

    _ASSERT(location == -1);


    glUniform4f(location, 1.0f, 1.0f, 1.0f, 1.0f);
}

void Shader::bind() {
    glUseProgram(Renderer_ID);
}

void Shader::unbind() {
    glUseProgram(0);
}


void Shader::SetUniform(float f1, float f2, float f3, float f4) {
    glUniform4f(location, f1, f2, f3, f4);
}


Shader::~Shader() {
    glDeleteProgram(Renderer_ID);
}



std::string Shader::openshader(std::string filePath) {
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

unsigned int Shader::compileshader(unsigned int type, const std::string& source) {
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



