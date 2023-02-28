#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>


static void GLclearerrors()
{
    while (glGetError());
}

static void GLCheckErrros() 
{
    while (GLenum error = glGetError()) 
    {
        std::cout << "[opengl error](" << error << ")" << std::endl;
    }
}
static std::string openshader(const char* filePath) {
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

static unsigned int compileshader(unsigned int type,const std::string& source) {
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


static unsigned int CreateShader() 
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileshader(GL_VERTEX_SHADER, openshader("res/shader/vertex.shader"));
    unsigned int fs = compileshader(GL_FRAGMENT_SHADER,openshader("res/shader/fragment.shader"));

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void createsqaure(float vertex1X,float vertex1Y, float vertex2X, float vertex2Y)
{
    float pos[8] =
    {
        vertex2X,vertex1Y,
        vertex1X,vertex2Y,
        vertex1X,vertex1Y,
        vertex2X,vertex2Y

    };

    unsigned int indexs[6] =
    {
        0,1,2,
        0,1,3
    };

    //create and save pos buffer on gpu
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), pos, GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


    //create and save index buffer on gpu
    unsigned int ibo;

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indexs, GL_STATIC_DRAW);
}

void updatesqaure(float vertex1X, float vertex1Y, float vertex2X, float vertex2Y)
{
    float pos[8] =
    {
        vertex2X,vertex1Y,
        vertex1X,vertex2Y,
        vertex1X,vertex1Y,
        vertex2X,vertex2Y

    };

    unsigned int indexs[6] =
    {
        0,1,2,
        0,1,3
    };
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), pos, GL_STATIC_DRAW);
}
int main(void)
{
    GLFWwindow* window;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "error!" << std::endl;
    }
    

    float pos[8] = {
         -0.5f, -0.5,
          0.5f, 0.5f,
          0.5f, -0.5f,
         -0.5f,0.5f
    };
    
    unsigned int indexs[6] =
    {
        0,1,2,
        0,1,3
    };
    //shader
    unsigned int shader = CreateShader();
    glUseProgram(shader);


    //uniform
    int location = glGetUniformLocation(shader, "u_color");
    _ASSERT(location != -1);
    glUniform4f(location, 0.2f, 0.6f, 1.0f, 0.0f);
    
    float width = 0.5f;
    float height = 0.1f;
    float Xoffset = 0.0f;
    float Yoffset = -0.6f;
    createsqaure(width + Xoffset, height + Yoffset, -width + Xoffset, -height + Yoffset);

    float speed = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        updatesqaure(width + Xoffset, height + Yoffset, -width + Xoffset, -height + Yoffset);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,nullptr);    

        if (width + Xoffset > 1.0f)
            speed = -0.05f;
        else if (width + Xoffset < 0.0f)
            speed = 0.05f;
        
        Xoffset += speed;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


