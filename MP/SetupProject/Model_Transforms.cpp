#pragma once
#include "Model_Transforms.h"

using namespace transformBase;

Transform::Transform() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	local_position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f);
	local_scale = glm::vec3(1.0f);

	pitch = 0.f;
	yaw = 0.f;
	roll = 0.f;
	local_pitch = 0.f;
	local_yaw = 0.f;
	local_roll = 0.f;
}

void Transform::Move(float x, float y, float z) {
	glm::vec3 move_amt = this->position + glm::vec3(x, y, z);
	this->InitPos(move_amt);
}

void Transform::Move(glm::vec3 vector) {
	this->InitPos(this->position + vector);
}

void Transform::InitPos(float x, float y, float z) {
	glm::vec3 new_pos = glm::vec3(x, y, z);
	this->InitPos(new_pos);
}

void Transform::InitPos(glm::vec3 vector) {
	this->position = vector;
}

void Transform::InitLocalPos(float x, float y, float z) {
	glm::vec3 new_pos = glm::vec3(x, y, z);
	this->local_position = new_pos;
}

void Transform::InitLocalPos(glm::vec3 vector) {
	this->local_position = vector;
}

void Transform::Rotate(RotationAxis axis, float theta) {
	switch (axis)
	{
	case RotationAxis::PITCH:
		this->InitRotation(axis, this->pitch + theta);
		break;
	case RotationAxis::YAW:
		this->InitRotation(axis, this->yaw + theta);
		break;
	case RotationAxis::ROLL:
		this->InitRotation(axis, this->roll + theta);
		break;
	}
}

void Transform::InitRotation(RotationAxis axis, float theta) {
	switch (axis)
	{
	case RotationAxis::PITCH:
		this->pitch = theta;
		break;
	case RotationAxis::YAW:
		this->yaw = theta;
		break;
	case RotationAxis::ROLL:
		this->roll = theta;
		break;
	}
}

void Transform::InitLocalRotation(RotationAxis axis, float theta) {
	switch (axis)
	{
	case RotationAxis::PITCH:
		this->local_pitch = theta;
		break;
	case RotationAxis::YAW:
		this->local_yaw = theta;
		break;
	case RotationAxis::ROLL:
		this->local_roll = theta;
		break;
	}
}

void Transform::Scale(glm::vec3 scalar) {
	this->InitScale(this->scale + scalar);
}

void Transform::Scale(float x, float y, float z) {
	glm::vec3 new_scalar = glm::vec3(x, y, z);
	this->InitScale(this->scale + new_scalar);
}

void Transform::Scale(float scalar) {
	glm::vec3 new_scalar = glm::vec3(scalar, scalar, scalar);
	this->InitScale(this->scale + new_scalar);
}

void Transform::InitScale(float x, float y, float z) {
	glm::vec3 new_scalar = glm::vec3(x, y, z);
	this->InitScale(new_scalar);
}

void Transform::InitScale(float scalar) {
	glm::vec3 new_scalar = glm::vec3(scalar, scalar, scalar);
	this->InitScale(new_scalar);
}

void Transform::InitScale(glm::vec3 scalar) {
	this->scale = scalar;
}

void Transform::InitLocalScale(float x, float y, float z) {
	glm::vec3 new_scalar = glm::vec3(x, y, z);
	this->InitLocalScale(new_scalar);
}

void Transform::InitLocalScale(float scalar) {
	glm::vec3 new_scalar = glm::vec3(scalar, scalar, scalar);
	this->InitLocalScale(new_scalar);
}

void Transform::InitLocalScale(glm::vec3 scalar) {
	this->local_scale = scalar;
}

glm::vec3 Transform::RetrievePosition() {
	return this->position + this->local_position;
}

glm::vec3 Transform::RetrievePos() {
	return this->position;
}

glm::vec3 Transform::RetrieveRotation() {
	return glm::vec3(pitch, yaw, roll);
}

glm::vec3 Transform::RetrieveFVector() {
	glm::vec3 forwardVector;
	forwardVector.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	forwardVector.y = sin(glm::radians(pitch));
	forwardVector.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));

	// Normalize forward vector first
	return glm::normalize(forwardVector);
}

glm::mat4 Transform::RetrieveModelMatrix() {
	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, position + local_position);
	model_matrix = glm::scale(model_matrix, scale * local_scale);
	model_matrix = glm::rotate(model_matrix, glm::radians(pitch + local_pitch), glm::vec3(1.f, 0.f, 0.f));
	model_matrix = glm::rotate(model_matrix, glm::radians(yaw + local_yaw), glm::vec3(0.f, 1.f, 0.f));
	model_matrix = glm::rotate(model_matrix, glm::radians(roll + local_roll), glm::vec3(0.f, 0.f, 1.f));

	return model_matrix;
}