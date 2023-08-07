#ifndef BASE_CLASS_NORMALS_HPP
#define BASE_CLASS_NORMALS_HPP

// add in stb_image //
#include "../../stb_image.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace normalBase
{
	class Normals
	{
	public:
		Normals(std::string strNorm);
		~Normals();

		GLuint RetrieveNormals();

	private:
		void InitNormals(std::string strNorm);

	protected:
		GLuint normals_texture;

	};
}
#endif