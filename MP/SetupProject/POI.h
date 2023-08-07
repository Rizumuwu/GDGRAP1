#ifndef ENTITY_CLUTTER_HPP
#define ENTITY_CLUTTER_HPP

#include "3Dmodel.h"
#include "Shader_Def.h"
#include "Texture_Def.h"
#include "Model_Transforms.h"
#include "Cam_Data.h"
#include "Light_Data.h"

//GLM HEADERS//
#include <glm/glm/gtc/type_ptr.hpp>

namespace PointOfInterest
{
	using namespace baseModel;
	using namespace transformBase;
	using namespace shaderBase;
	using namespace textureBase;

	class POI
	{
	public:
		POI();

		virtual void Initialize(std::string strMesh, std::string strTex, std::string strVert, std::string strFrag);
		void Draw(CameraData cameraData, LightData pointLight, LightData directionalLight);
		Transform* RetrieveTransform();

	private:
		void InitVert();

	private:
		ThreeDimensionalModel* model;
		Shader* shader;
		Texture* texture;
		Transform* transform;
	};
}
#endif
