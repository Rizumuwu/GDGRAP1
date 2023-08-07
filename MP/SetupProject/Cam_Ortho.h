#pragma once
#ifndef CAMERA_ORTHOGRAPHIC_CAMERA_HPP
#define CAMERA_ORTHOGRAPHIC_CAMERA_HPP

#include "Cam.h"

namespace Camera
{
	class Orthographic : public Cam
	{
	public:
		Orthographic();

		glm::mat4 GetProjMatrix();
		CameraData GetCamData();

		void InitSize(float);
		void UpdateSize(float);

		glm::vec3 GetPosition() { 
			return pos; 
		}
		
		void SetPosition(glm::vec3 pos) { 
			this->pos = pos; 
		}

	private:
		glm::vec3 pos;
		float size;
	};
}
#endif
