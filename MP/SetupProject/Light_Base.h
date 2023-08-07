#pragma once
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include "Light_Data.h"

namespace light
{
	class Light
	{
	public:
		Light();

		virtual void InitLightData(LightData data) = 0;
		virtual LightData RetrieveLightData() = 0;
		void InitLightColor(glm::vec3);
		void InitAmbientColor(glm::vec3);
		void InitIntensity(float);

	protected:
		glm::vec3 light_color;
		glm::vec3 ambient_color;
		float ambient_str;
		float spec_str;
		float spec_phong;
		float intensity;
	};
}
#endif
