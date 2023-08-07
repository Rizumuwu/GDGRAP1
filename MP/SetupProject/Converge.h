#pragma once
#ifndef CONTROLLER_GAME_HPP
#define CONTROLLER_GAME_HPP

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//GLM HEADERS//
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Window_Stuff.h"
#include "Player_Char.h"
#include "POI.h"
#include "Worldspace.h"
#include "Light_Directional.h"

namespace Controller
{
	using namespace character;
	using namespace worldSpace;
	using namespace light;
	using namespace PointOfInterest;

	class Game
	{
	public:
		Game();
		void InitPOI();
		void Run();

	private:
		//Game object variables
		Character* character;
		Worldspace* world;
		Directional* Moon;
		std::vector<POI*> POIList;

	private:
		void Initialize();
		void ProcessInput();
		void Update(float tDeltaTime);
		void Render();

	private:
		GLFWwindow* gameWindow;

	};
}


#endif

