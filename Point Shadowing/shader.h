#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
	GLuint ID; // 程序ID
	// 构造器读取并构建着色器
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	// 使用激活函数
	void use(); 
	// uniform工具函数
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, float x, float y);
	void setVec3(const std::string& name, float x, float y, float z);
	void setVec4(const std::string& name, float x, float y, float z, float w);
	void setVec2(const std::string& name, const glm::vec2& v);
	void setVec3(const std::string& name, const glm::vec3& v);
	void setVec4(const std::string& name, const glm::vec4& v);
	void setMat4(const std::string& name, const glm::mat4& mat);
	
};

#endif
