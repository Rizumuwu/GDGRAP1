#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Vehicle.h"
#include "Cam_Pers.h"
#include "Cam_Ortho.h"
#include "Light_Point.h"

#include "Light_Intensity.h"
#include "Cam_Types.h"

namespace character
{
	using namespace light;
	using namespace Camera;
	using namespace vehicle;

	class Character
	{
	public:
		Character();

		void CreateBEV();

		void CheckInputs(GLFWwindow*);
		void Update(float);
		void BEVMove(float);
		void BEVToggle();
		void ResetBEV();
		void Draw();

		CameraData RetrieveCamData();
		LightData RetrievePointData();

		void InitDirectionalData(LightData);

	private:
		void TPCMove(float);
		void ResetScope();
		void FPCMove(float);
		void PerspectiveToggle();
		void CharLightToggle();

	private:
		void CreateVehicleLight();
		void CreateFPC();
		void CreateTPC();
		const glm::vec3 PointForward();

	private:
		Vehicle* playerVehicle;
		Point* playerLight;
		Perspective* playerTPC;
		Perspective* playerFPC;
		Orthographic* playerBEV;

		PointIntensity CurrLightIntensity;
		ActiveCam CurrActiveCam;
		ActiveCam PrevActiveCam;

		LightData playerDirectionalData;

	private:
		bool pressW;
		bool pressS;
		bool pressA;
		bool pressD;
		bool pressQ;
		bool pressE;
		bool pressF;
		bool press1;
		bool press2;

		bool playerLightToggle;
		bool playerCamToggle;
		bool playerTopToggle;

		double currMouseX;
		double currMouseY;
		double prevMouseX;
		double prevMouseY;

	private:
		const float zoomInSPD = 50.0f;
		const float moveSPD = 100.0f;
		const float rotationSPD = 100.0f;
		const float LOW_INTENSITY = 30.0f;
		const float MID_INTENSITY = 130.0f;
		const float HIGH_INTENSITY = 330.0f;

	};
}
#endif

