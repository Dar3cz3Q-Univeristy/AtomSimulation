#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader
{
public:
	Shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
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
	
