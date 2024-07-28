#include <string>
#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		// ���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		// ���ļ��е����ݶ�ȡ����������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// �ر��ļ�������
		vShaderFile.close();
		fShaderFile.close();

		// ת����������string��
		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	int success;
	char infoLog[512];

	// ������ɫ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// ��ӡ����
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}

	// Ƭ����ɫ��
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// ��ӡ����
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}

	// ��ɫ����������
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	// ��ӡ���Ӵ�����Ϣ
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::LINKING_FAILED\n"
			<< infoLog << std::endl;
	}

	// ɾ����ɫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}
// ʹ�ü����
void Shader::use() {
	glUseProgram(ID);
}
// uniform���ߺ���
void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) {
	int modelLoc = glGetUniformLocation(this->ID, name.c_str());
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec2(const std::string& name, float x, float y) {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setVec2(const std::string& name, const glm::vec2& v) {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), v.x, v.y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& v) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), v.x, v.y, v.z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& v) {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), v.x, v.y, v.z, v.w);
}

