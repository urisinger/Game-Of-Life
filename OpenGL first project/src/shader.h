#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader {
public:
	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	~Shader();


	void SetUniform(float f1,float f2, float f3,float f4);
	void bind();
	void unbind();

private:
	unsigned int Renderer_ID;
	unsigned int location;
	unsigned int CompileShader(unsigned int type, const std::string& source);
	std::string OpenShader(std::string filepath);
};