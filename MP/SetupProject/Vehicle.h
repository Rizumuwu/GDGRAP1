#ifndef ENTITY_TANK_HPP
#define ENTITY_TANK_HPP

#include "3Dmodel.h"
#include "Shader_Def.h"
#include "Texture_Def.h"
#include "Normal_Data.h"
#include "Model_Transforms.h"
#include "Cam_Data.h"
#include "Light_Data.h"

//GLM HEADERS//
#include <glm/glm/gtc/type_ptr.hpp>

namespace vehicle
{
	using namespace baseModel;
	using namespace normalBase;
	using namespace transformBase;
	using namespace textureBase;
	using namespace shaderBase;

	class Vehicle
	{
	public:
		Vehicle();

		void Draw(CameraData, LightData, LightData);
		Transform* RetrieveTransform();

	private:
		void InitVert();

	private:
		ThreeDimensionalModel* model;
		Shader* shader;
		Texture* texture;
		Normals* normals;
		Transform* transform;

		//Store file paths
		const std::string meshPath = "3D/Vehicle/Tank_Model.obj";
		const std::string textPath = "3D/Vehicle/Tank_Texture.jpg";
		const std::string normPath = "3D/Vehicle/Tank_Normal.jpg";
		const std::string vertPath = "Shaders/vehicle.vert";
		const std::string fragPath = "Shaders/vehicle.frag";
	};
}
#endif
