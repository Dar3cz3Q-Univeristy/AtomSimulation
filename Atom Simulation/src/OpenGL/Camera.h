#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "Renderer.h"
#include "Shader.h"

class Camera
{
public:
	Camera();
	Camera(int width, int height, glm::vec3 position);
	void Matrix(Shader& shader, const std::string& uniform) const;
	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Inputs(GLFWwindow* window);
	void UpdateWidth(int width) { m_Width = width; };
	void UpdateHeight(int height) { m_Height = height; };
private:
	glm::vec3 m_Position;
	glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_CameraMatrix = glm::mat4(1.0f);
	bool m_FirstClick = true;
	int m_Width;
	int m_Height;
	float m_Speed = 0.1f;
	float m_Sensitivity = 100.0f;
};

