#pragma once
#include "Light_Base.h"

using namespace light;

Light::Light() {
	light_color = glm::vec3(0.0f, 0.0f, 0.0f);
	ambient_color = glm::vec3(0.0f, 0.0f, 0.0f);
	ambient_str = 0.0f;
	spec_str = 0.0f;
	spec_phong = 0.0f;
	intensity = 0.0f;
}

void Light::InitLightColor(glm::vec3 lightColor) {
	light_color = lightColor;
}

void Light::InitAmbientColor(glm::vec3 ambientColor) {
	ambient_color = ambientColor;
}

void Light::InitIntensity(float intensity) {
	this->intensity = intensity;
}

