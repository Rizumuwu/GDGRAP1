#ifndef ENTITY_ENVIRONMENT_HPP
#define ENTITY_ENVIRONMENT_HPP

#include "Shader_Def.h"
#include "Skybox.h"
#include "Cam_Data.h"

//GLM HEADERS//
#include <glm/glm/gtc/type_ptr.hpp>

namespace worldSpace
{
	using namespace shaderBase;
	using namespace skyBase;

	class Worldspace
	{
	public:
		Worldspace();

		void Draw(CameraData data);

	private:
		void LoadVertices();

	private:
		Shader* shader;
		SkyBox* skybox;

	private:
		const std::string vertPath = "Shaders/skybox.vert";
		const std::string fragPath = "Shaders/skybox.frag";
		const std::vector<std::string> filePaths
		{
			"3D/Skybox/posx.jpg",
				"3D/Skybox/negx.jpg",
				"3D/Skybox/posy.jpg",
				"3D/Skybox/negy.jpg",
				"3D/Skybox/posz.jpg",
				"3D/Skybox/negz.jpg"
		};

		const  unsigned int skyboxIndices[36]{
			1,2,6,
			6,5,1,

			0,4,7,
			7,3,0,

			4,5,6,
			6,7,4,

			0,3,2,
			2,1,0,

			0,1,5,
			5,4,0,

			3,7,6,
			6,2,3
		};

		const float skyboxVertices[24]{
			-1.f, -1.f, 1.f,
			1.f, -1.f, 1.f,
			1.f, -1.f, -1.f,
			-1.f, -1.f, -1.f,
			-1.f, 1.f, 1.f,
			1.f, 1.f, 1.f,
			1.f, 1.f, -1.f,
			-1.f, 1.f, -1.f
		};
	};
}
#endif
