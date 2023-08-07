#include "Player_Char.h"
#include <iostream>

using namespace character;
using namespace Camera;

Character::Character() {
	pressW = false;
	pressS = false;
	pressA = false;
	pressD = false;
	pressQ = false;
	pressE = false;
	pressF = false;
	press1 = false;
	press2 = false;

	currMouseX = 0.0f;
	currMouseY = 0.0f;

	prevMouseX = 0.0f;
	prevMouseY = 0.0f;

	playerLightToggle = false;
	playerCamToggle = false;
	playerTopToggle = false;

	//Set character defaults
	this->CurrLightIntensity = PointIntensity::LOW;
	this->CurrActiveCam = ActiveCam::THIRDPERSON;
	this->PrevActiveCam = ActiveCam::THIRDPERSON;

	//Initialize character components
	this->playerVehicle = new Vehicle();
	CreateVehicleLight();
	CreateTPC();
	CreateFPC();
	CreateBEV();
}

void Character::CreateVehicleLight() {
	//Default light values
	LightData startLightData;
	startLightData.light_position = glm::vec3(0.0f, 0.0f, 0.0f);
	startLightData.light_color = glm::vec3(0.0f, 0.8f, 0.2f);
	startLightData.ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
	startLightData.ambient_str = 0.2f;
	startLightData.spec_str = 0.5f;
	startLightData.spec_phong = 16.0f;
	startLightData.intensity = LOW_INTENSITY;

	this->playerLight = new Point();
	this->playerLight->RetrieveTransform()->InitLocalPos(glm::vec3(0.0f, 0.0f, 10.0f));
	this->playerLight->InitLightData(startLightData);
}

void Character::CreateFPC() {
	this->playerFPC = new Perspective();
	this->playerFPC->RetrieveTransform()->InitLocalPos(glm::vec3(0.0f, 5.0f, 0.0f));
	this->playerFPC->InitCenter(PointForward());
	this->playerFPC->InitFOV(30.0f);
	this->playerFPC->SetFP(225.0f);
}

void Character::CreateTPC() {
	this->playerTPC = new Perspective();
	this->playerTPC->RetrieveTransform()->InitLocalPos(glm::vec3(0.0f, 10.0f, -15.0f));
	this->playerTPC->InitCenter(this->playerVehicle->RetrieveTransform()->RetrievePosition());
	this->playerTPC->InitFOV(60.0f);
	this->playerTPC->SetFP(150.0f);
}

void Character::CreateBEV() {
	this->playerBEV = new Orthographic();
	this->playerBEV->SetPosition(glm::vec3(0.0f, 20.0f, -1.0f));
	this->playerBEV->InitCenter(this->playerVehicle->RetrieveTransform()->RetrievePosition());
	this->playerBEV->InitSize(45.0f);
	this->playerBEV->SetFP(100.0f);
}

void Character::CheckInputs(GLFWwindow* window) {
	this->pressW = glfwGetKey(window, GLFW_KEY_W);
	this->pressS = glfwGetKey(window, GLFW_KEY_S);
	this->pressA = glfwGetKey(window, GLFW_KEY_A);
	this->pressD = glfwGetKey(window, GLFW_KEY_D);
	this->pressQ = glfwGetKey(window, GLFW_KEY_Q);
	this->pressE = glfwGetKey(window, GLFW_KEY_E);
	this->pressF = glfwGetKey(window, GLFW_KEY_F);

	this->press1 = glfwGetKey(window, GLFW_KEY_1);
	this->press2 = glfwGetKey(window, GLFW_KEY_2);

	glfwGetCursorPos(window, &this->currMouseX, &this->currMouseY);
}

void Character::Update(float tDeltaTime) {
	CharLightToggle();
	BEVToggle();

	switch (CurrActiveCam) {
		//Toggle only when perspective cam
	case ActiveCam::THIRDPERSON:
		TPCMove(tDeltaTime);
		PerspectiveToggle();
		break;

	case ActiveCam::FIRSTPERSON:
		FPCMove(tDeltaTime);
		PerspectiveToggle();
		break;

	case ActiveCam::BIRDSEYE:
		BEVMove(tDeltaTime);
		break;
	}
}

void Character::BEVMove(float tDeltaTime) {
	float movement = moveSPD * tDeltaTime;

	if (this->pressW) {
		this->playerBEV->SetPosition(glm::vec3(0.0f, 0.0f, movement) + this->playerBEV->GetPosition());
		this->playerBEV->MoveCenter(glm::vec3(0.0f, 0.0f, movement));
	}

	if (this->pressS) {
		this->playerBEV->SetPosition(glm::vec3(0.0f, 0.0f, -movement) + this->playerBEV->GetPosition());
		this->playerBEV->MoveCenter(glm::vec3(0.0f, 0.0f, -movement));
	}

	if (this->pressA) {
		this->playerBEV->SetPosition(glm::vec3(movement, 0.0f, 0.0f) + this->playerBEV->GetPosition());
		this->playerBEV->MoveCenter(glm::vec3(movement, 0.0f, 0.0f));
	}

	if (this->pressD) {
		this->playerBEV->SetPosition(glm::vec3(-movement, 0.0f, 0.0f) + this->playerBEV->GetPosition());
		this->playerBEV->MoveCenter(glm::vec3(-movement, 0.0f, 0.0f));
	}
}

//Change Bird Eye View to previous setting
void Character::BEVToggle() {

	if (this->press2 && !this->playerTopToggle) {
		this->playerTopToggle = true;

		switch (CurrActiveCam) {
		case ActiveCam::BIRDSEYE:
			this->CurrActiveCam = this->PrevActiveCam;
			break;

		default:
			ResetBEV();
			this->CurrActiveCam = ActiveCam::BIRDSEYE;
			break;
		}
	}
	else if (!this->press2) {
		this->playerTopToggle = false;
	}
}

//Reset BEV
void Character::ResetBEV() {
	this->playerBEV->SetPosition(this->playerVehicle->RetrieveTransform()->RetrievePosition() + glm::vec3(0.0, 20.0, -1.0f));
	this->playerBEV->InitCenter(this->playerVehicle->RetrieveTransform()->RetrievePosition());
}

//Function for First Person cam movement
void Character::FPCMove(float tDeltaTime) {
	Transform* cameraTransform = this->playerFPC->RetrieveTransform();

	if (this->pressW) {
		cameraTransform->Rotate(RotationAxis::PITCH, rotationSPD * tDeltaTime);
		this->playerFPC->InitCenter(PointForward());
	}

	if (this->pressS) {
		cameraTransform->Rotate(RotationAxis::PITCH, -rotationSPD * tDeltaTime);
		this->playerFPC->InitCenter(PointForward());
	}

	if (this->pressA) {
		cameraTransform->Rotate(RotationAxis::YAW, rotationSPD * tDeltaTime);
		this->playerFPC->InitCenter(PointForward());
	}

	if (this->pressD) {
		cameraTransform->Rotate(RotationAxis::YAW, -rotationSPD * tDeltaTime);
		this->playerFPC->InitCenter(PointForward());
	}

	if (this->pressQ) {
		this->playerFPC->UpdateFOV(this->zoomInSPD * -tDeltaTime);
	}

	if (this->pressE) {
		this->playerFPC->UpdateFOV(this->zoomInSPD * tDeltaTime);
	}
}

//toggle between first and third person view
void Character::PerspectiveToggle() {
	if (this->press1 && !this->playerCamToggle) {
		
		this->playerCamToggle = true;
		
		switch (CurrActiveCam) {
		case ActiveCam::FIRSTPERSON:
			this->CurrActiveCam = ActiveCam::THIRDPERSON;
			this->PrevActiveCam = ActiveCam::THIRDPERSON;
			break;

		case ActiveCam::THIRDPERSON:
			this->CurrActiveCam = ActiveCam::FIRSTPERSON;
			this->PrevActiveCam = ActiveCam::FIRSTPERSON;
			break;

		default:
			break;
		}
	}
	else if (!this->press1)
		this->playerCamToggle = false;
}

//Function for altering light intensity
void Character::CharLightToggle() {

	if (this->pressF && !this->playerLightToggle) {
		this->playerLightToggle = true;
		switch (CurrLightIntensity) {
		case PointIntensity::LOW:
			this->CurrLightIntensity = PointIntensity::MID;
			this->playerLight->InitIntensity(MID_INTENSITY);
			break;

		case PointIntensity::MID:
			this->CurrLightIntensity = PointIntensity::HIGH;
			this->playerLight->InitIntensity(HIGH_INTENSITY);
			break;

		case PointIntensity::HIGH:
			this->CurrLightIntensity = PointIntensity::LOW;
			this->playerLight->InitIntensity(LOW_INTENSITY);
			break;

		default:
			break;
		}
	}
	else if (!this->pressF)
		this->playerLightToggle = false;
}

//Function for movement during Third person view
void Character::TPCMove(float tDeltaTime)
{
	double dDeltaX = this->currMouseX - this->prevMouseX;
	double dDeltaY = this->currMouseX - this->prevMouseY;

	this->prevMouseX = this->currMouseX;
	this->prevMouseY = this->currMouseY;

	std::vector<Transform*> playerTransforms;

	playerTransforms.push_back(this->playerVehicle->RetrieveTransform());
	playerTransforms.push_back(this->playerFPC->RetrieveTransform());
	playerTransforms.push_back(this->playerTPC->RetrieveTransform());
	playerTransforms.push_back(this->playerLight->RetrieveTransform());

	if (this->pressW) {
		glm::vec3 movement = playerTransforms[0]->RetrieveFVector() * moveSPD * tDeltaTime;

		//Move things forward depending on forward definition at the moment
		for (Transform* object : playerTransforms)
			object->Move(movement);

		//Set camera above mesh again
		playerTransforms[1]->InitPos(playerTransforms[0]->RetrievePosition());
		playerTransforms[1]->InitLocalPos(glm::vec3(0.0f, 5.0f, 0.0f));

		playerTPC->MoveCenter(movement);
		ResetScope();
	}

	if (this->pressS) {
		glm::vec3 movement = playerTransforms[0]->RetrieveFVector() * -moveSPD * tDeltaTime;

		for (Transform* object : playerTransforms)
			object->Move(movement);

		playerTransforms[1]->InitPos(playerTransforms[0]->RetrievePosition());
		playerTransforms[1]->InitLocalPos(glm::vec3(0.0f, 5.0f, 0.0f));

		playerTPC->MoveCenter(movement);
		ResetScope();
	}

	if (this->pressA) {
		float rotationAmount = rotationSPD * tDeltaTime;

		playerTransforms[0]->Rotate(RotationAxis::YAW, rotationAmount);
		playerTransforms[2]->Rotate(RotationAxis::YAW, rotationAmount);

		playerTransforms[2]->InitLocalPos((playerTransforms[0]->RetrieveFVector() * -10.0f)
			+ glm::vec3(0.0f, 5.0f, 0.0f));

		//First person cam a bit forward of character mesh
		playerTransforms[3]->InitLocalPos((playerTransforms[0]->RetrieveFVector() * 10.0f));

		//reset third person cam center
		playerTPC->InitCenter(playerTransforms[2]->RetrievePosition() + playerTransforms[2]->RetrieveFVector());

		ResetScope();
	}

	if (this->pressD) {
		float rotationAmount = -rotationSPD * tDeltaTime;

		playerTransforms[0]->Rotate(RotationAxis::YAW, rotationAmount);

		playerTransforms[2]->InitLocalPos((playerTransforms[0]->RetrieveFVector() * -10.0f)
			+ glm::vec3(0.0f, 5.0f, 0.0f));
		playerTransforms[2]->Rotate(RotationAxis::YAW, rotationAmount);
		playerTransforms[3]->InitLocalPos((playerTransforms[0]->RetrieveFVector() * 10.0f));

		playerTPC->InitCenter(playerTransforms[2]->RetrievePosition() + playerTransforms[2]->RetrieveFVector());
		ResetScope();
	}

	//Third person rotation using mouse
	if (dDeltaX > 50.0f) {
		playerTPC->RetrieveTransform()->Rotate(RotationAxis::YAW, -rotationSPD * tDeltaTime);
		playerTPC->InitCenter(playerTransforms[2]->RetrievePosition() + playerTransforms[2]->RetrieveFVector());
	}

	if (dDeltaX < -50.0f)
	{
		playerTPC->RetrieveTransform()->Rotate(RotationAxis::YAW, rotationSPD * tDeltaTime);
		playerTPC->InitCenter(playerTransforms[2]->RetrievePosition() + playerTransforms[2]->RetrieveFVector());
	}

	if (dDeltaY > 50.0f)
	{
		playerTPC->RetrieveTransform()->Rotate(RotationAxis::PITCH, -rotationSPD * tDeltaTime);
		playerTPC->InitCenter(playerTransforms[2]->RetrievePosition() + playerTransforms[2]->RetrieveFVector());
	}

	if (dDeltaY < -50.0f)
	{
		playerTPC->RetrieveTransform()->Rotate(RotationAxis::PITCH, rotationSPD * tDeltaTime);
		playerTPC->InitCenter(playerTransforms[2]->RetrievePosition() + playerTransforms[2]->RetrieveFVector());
	}
}

// match first person cam with mesh rotation
void Character::ResetScope() {
	glm::vec3 rotation = this->playerVehicle->RetrieveTransform()->RetrieveRotation();
	this->playerFPC->RetrieveTransform()->InitRotation(RotationAxis::PITCH, rotation.x);
	this->playerFPC->RetrieveTransform()->InitRotation(RotationAxis::YAW, rotation.y);
	this->playerFPC->RetrieveTransform()->InitRotation(RotationAxis::ROLL, rotation.z);
	this->playerFPC->InitCenter(PointForward());
}

void Character::Draw() {
	LightData pointLightData = this->playerLight->RetrieveLightData();
	CameraData cameraData = RetrieveCamData();

	playerVehicle->Draw(cameraData, pointLightData, this->playerDirectionalData);
}

const glm::vec3 Character::PointForward() {
	glm::vec3 Forward = this->playerFPC->RetrieveTransform()->RetrieveFVector() * 1000.0f;
	Forward += this->playerFPC->RetrieveTransform()->RetrieveFVector();
	return Forward;
}

//Utility function to get camera data
CameraData Character::RetrieveCamData() {
	CameraData cameraData;

	switch (CurrActiveCam) {
	case ActiveCam::THIRDPERSON:
		cameraData = this->playerTPC->GetCamData();
		cameraData.isFPS = false;
		break;

	case ActiveCam::FIRSTPERSON:
		cameraData = this->playerFPC->GetCamData();
		cameraData.isFPS = true;
		break;

	case ActiveCam::BIRDSEYE:
		cameraData = this->playerBEV->GetCamData();
		cameraData.isFPS = false;
		break;
	}

	return cameraData;
}

LightData Character::RetrievePointData() {
	return this->playerLight->RetrieveLightData();
}

void Character::InitDirectionalData(LightData data) {
	this->playerDirectionalData = data;
}