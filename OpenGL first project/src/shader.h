#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader {
public:
	Shader(std::string VertexFilePath, std::string FragmentFilePath);
	~Shader();


	void SetUniform(float f1,float f2, float f3,float f4);
	void bind();
	void unbind();

private:
	unsigned int Renderer_ID;
	int location;
	unsigned int compileshader(unsigned int type, const std::string& source);
	std::string openshader(std::string filepath);
};