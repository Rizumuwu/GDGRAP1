#pragma once
#include "Cam_Ortho.h"

using namespace Camera;

Orthographic::Orthographic() {
	this->size = 2.0f;
}

glm::mat4 Orthographic::GetProjMatrix() {
	return glm::ortho(-size, size, -size, size, this->nearPlane, this->farPlane);
}

void Orthographic::InitSize(float size) {
	this->size = size;
}

void Orthographic::UpdateSize(float value) {
	InitSize(this->size + value);
}

CameraData Orthographic::GetCamData() {
	CameraData data;
	data.camera_pos = this->transform->RetrievePosition();
	data.view_matrix = glm::lookAt(this->pos, this->cameraCenter, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
	data.projection_matrix = this->GetProjMatrix();
	return data;
}