#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Model_Transforms.h"
#include "Cam_Data.h"

namespace Camera
{
	using namespace transformBase;

	class Cam
	{
	public:
		Cam();

		void InitCam(glm::vec3);
		void MoveCam(glm::vec3);

		void InitCenter(glm::vec3);
		void MoveCenter(glm::vec3);

		void InitPosCen(glm::vec3, glm::vec3);
		void MovePosCen(glm::vec3, glm::vec3);

		void SetNP(float);
		void SetFP(float);

		glm::mat4 RetrieveViewMatrix();
		Transform* RetrieveTransform();

		virtual glm::mat4 GetProjMatrix() = 0;
		virtual CameraData GetCamData() = 0;

	protected:
		const glm::vec3 WORLD_UP = glm::normalize(glm::vec3(0.f, 1.f, 0.f));

		Transform* transform;
		glm::vec3 cameraCenter;

		float nearPlane;
		float farPlane;
	};

}
#endif
