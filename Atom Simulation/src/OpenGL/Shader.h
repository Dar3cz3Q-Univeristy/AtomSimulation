#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <array>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Specification.h"

class Shader
{
public:
	Shader();
	~Shader();

	void Init(const std::string& vertex_filepath, const std::string& fragment_filepath);
	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3fv(const std::string& name, const std::vector<glm::vec3>& data);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform4fv(const std::string& name, const std::vector<glm::vec4>& data);
	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	unsigned int m_RendererID;
	std::string m_VertexFilePath;
	std::string m_FragmentFilePath;

	// Caching uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;

	std::string ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};
	
