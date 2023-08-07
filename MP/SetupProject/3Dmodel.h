#pragma once
#ifndef BASE_CLASS_MODEL_HPP
#define BASE_CLASS_MODEL_HPP

#include "../../tiny_obj_loader.h"

//GLM HEADERS//
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "Shader_Def.h"

namespace baseModel
{
	class ThreeDimensionalModel
	{
	public:
		ThreeDimensionalModel(std::string);
		~ThreeDimensionalModel();

		GLuint VAOReference();
		GLuint VBOReference();
		std::vector<GLfloat> VertexData();

	private:
		void InitializeModel(std::string);

	protected:
		GLuint VAO, VBO;
		std::vector<GLfloat> fullVertexData;
	};
}

#endif