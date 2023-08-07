#pragma once
#ifndef BASE_CLASS_SKYBOX_HPP
#define BASE_CLASS_SKYBOX_HPP

// add in stb_image //
#include "../../stb_image.h"


//GLM HEADERS//
#include "glad/glad.h"
#include <glm/glm/glm.hpp>

#include <string>
#include <vector>

namespace skyBase
{
	class SkyBox
	{
	public:
		//Constructor and deconstructor
		SkyBox(std::vector<std::string> strFileNames);
		~SkyBox();

		//Utility functions
		GLuint GetTexture();
		GLuint GetVAO();
		GLuint GetVBO();
		GLuint GetEBO();

	private:
		void LoadTextures(std::vector<std::string> strFileNames);

	private:
		GLuint VAO, VBO, EBO;
		GLuint texture;
	};
}
#endif