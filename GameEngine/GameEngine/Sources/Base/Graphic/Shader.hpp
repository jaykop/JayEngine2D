#ifndef _SHADER_HPP
#define _SHADER_HPP

class Shader{
public:

	Shader();
	~Shader();

	void LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

	GLuint m_programID;

private:

	
};

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif