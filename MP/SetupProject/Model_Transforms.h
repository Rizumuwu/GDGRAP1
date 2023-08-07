#pragma once
#ifndef BASE_CLASS_TRANSFORM_HPP
#define BASE_CLASS_TRANSFORM_HPP

#include <vector>

//GLM HEADERS//
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "Rotations.h"

namespace transformBase
{
	class Transform
	{
	public:
		Transform();

		//Retrieval Funcs
		glm::vec3 RetrievePosition();
		glm::vec3 RetrieveRotation();
		glm::vec3 RetrieveFVector();
		glm::mat4 RetrieveModelMatrix();
		glm::vec3 RetrievePos();

		//Translation Funcs
		void Move(float x, float y, float z);
		void Move(glm::vec3 vector);
		void InitPos(float x, float y, float z);
		void InitPos(glm::vec3 vector);
		void InitLocalPos(float x, float y, float z);
		void InitLocalPos(glm::vec3 vector);

		//Rotation Funcs
		void Rotate(RotationAxis axis, float theta);
		void InitRotation(RotationAxis axis, float theta);
		void InitLocalRotation(RotationAxis axis, float theta);

		//Scale Funcs
		void Scale(float x, float y, float z);
		void Scale(float scalar);
		void Scale(glm::vec3 scalar);
		void InitScale(float x, float y, float z);
		void InitScale(float scalar);
		void InitScale(glm::vec3 scalar);
		void InitLocalScale(float x, float y, float z);
		void InitLocalScale(float scalar);
		void InitLocalScale(glm::vec3 scalar);

	private:
		float pitch;
		float yaw;
		float roll;
		float local_pitch;
		float local_yaw;
		float local_roll;

		glm::vec3 position;
		glm::vec3 local_position;
		glm::vec3 scale;
		glm::vec3 local_scale;
	};
}


#endif