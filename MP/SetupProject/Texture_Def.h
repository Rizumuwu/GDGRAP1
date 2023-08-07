#ifndef BASE_CLASS_TEXTURE_HPP
#define BASE_CLASS_TEXTURE_HPP

// add in stb_image //
#include "../../stb_image.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace textureBase
{
	class Texture
	{
	public:
		Texture(std::string strTex);
		~Texture();

		GLuint GetTexture();

	private:
		void LoadTexture(std::string strTex);

	protected:
		GLuint texture;

	};
}
#endif
