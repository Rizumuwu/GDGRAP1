#pragma once
#ifndef LIGHT_DIRECTIONAL_LIGHT_HPP
#define LIGHT_DIRECTIONAL_LIGHT_HPP

#include "Light_Base.h"

namespace light
{
	class Directional : public Light
	{
	public:
		Directional();
		void InitDir(glm::vec3 direction);
		void InitLightData(LightData data);
		LightData RetrieveLightData();

	private:
		glm::vec3 lightDir;
	};
}
#endif