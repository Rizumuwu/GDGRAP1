#pragma once
#ifndef CAMERA_DATA_HPP
#define CAMERA_DATA_HPP

//GLM HEADERS//
#include <glm/glm/glm.hpp>

struct CameraData
{
	glm::vec3 camera_pos = glm::vec3(0.0f);
	glm::mat4 view_matrix = glm::mat4(1.0f);
	glm::mat4 projection_matrix = glm::mat4(1.0f);
	bool isFPS = false;
};

#endif
