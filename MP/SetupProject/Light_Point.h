#pragma once
#ifndef LIGHT_POINT_LIGHT_HPP
#define LIGHT_POINT_LIGHT_HPP

#include "Light_Base.h"
#include "Model_Transforms.h"

namespace light
{
	using namespace transformBase;
	class Point : public Light
	{
	public:
		Point();
		void InitLightData(LightData data);
		LightData RetrieveLightData();
		Transform* RetrieveTransform();

	private:
		Transform* transform;
	};
}
#endif

