#pragma once
#ifndef CAMERA_PERSPECTIVE_CAMERA_HPP
#define	CAMERA_PERSPECTIVE_CAMERA_HPP

#include "Cam.h"
#include "Window_stuff.h"

namespace Camera
{
	class Perspective : public Cam
	{
		public:
			Perspective();

			glm::mat4 GetProjMatrix();
			CameraData GetCamData();
			void InitFOV(float);
			void UpdateFOV(float);

		private:
			const float ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
			float FOV;
	};
}

#endif
