#pragma once
#include "Cam_Pers.h"

using namespace Camera;

Perspective::Perspective() {
	this->FOV = 60.0f;
}

glm::mat4 Perspective::GetProjMatrix() {
	return glm::perspective(glm::radians(this->FOV), ASPECT_RATIO, this->nearPlane, this->farPlane);
}

void Perspective::InitFOV(float FOV) {
	this->FOV = FOV;
}

void Perspective::UpdateFOV(float inc) {
	InitFOV(this->FOV + inc);
}

CameraData Perspective::GetCamData() {
	CameraData data;
	data.camera_pos = this->transform->RetrievePosition();
	data.view_matrix = this->RetrieveViewMatrix();
	data.projection_matrix = this->GetProjMatrix();
	return data;
}