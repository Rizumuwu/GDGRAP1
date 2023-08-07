#pragma once
#include "Cam.h"

using namespace Camera;

Cam::Cam()
{
	this->nearPlane = 0.1f;
	this->farPlane = 100.0f;
	this->transform = new Transform();
	this->cameraCenter = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Cam::InitCam(glm::vec3 pos)
{
	this->transform->InitPos(pos);
}

void Cam::MoveCam(glm::vec3 pos)
{
	this->InitCam(this->transform->RetrievePosition() + pos);
}

void Cam::InitCenter(glm::vec3 camCenter)
{
	this->cameraCenter = camCenter;
}

void Cam::MoveCenter(glm::vec3 camCenter)
{
	this->InitCenter(this->cameraCenter + camCenter);
}

void Cam::InitPosCen(glm::vec3 pos, glm::vec3 camCenter)
{
	this->InitCam(pos);
	this->InitCenter(camCenter);
}
void Cam::MovePosCen(glm::vec3 pos, glm::vec3 camCenter)
{
	this->MoveCam(pos);
	this->MoveCenter(camCenter);
}

void Cam::SetNP(float near)
{
	nearPlane = near;
}

void Cam::SetFP(float far)
{
	farPlane = far;
}

glm::mat4 Cam::RetrieveViewMatrix()
{
	glm::mat4 view_matrix = glm::lookAt(this->transform->RetrievePosition(), this->cameraCenter, WORLD_UP);
	return view_matrix;
}

Transform* Cam::RetrieveTransform()
{
	return this->transform;
}