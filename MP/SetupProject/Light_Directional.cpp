#pragma once
#include "Light_Directional.h"

using namespace light;

Directional::Directional() {
	this->lightDir = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Directional::InitDir(glm::vec3 direction) {
	this->lightDir = direction;
}

void Directional::InitLightData(LightData data) {
	this->lightDir = data.light_direction;
	this->light_color = data.light_color;
	this->ambient_color = data.ambient_color;
	this->ambient_str = data.ambient_str;
	this->spec_str = data.spec_str;
	this->spec_phong = data.spec_phong;
	this->intensity = data.intensity;
}

LightData Directional::RetrieveLightData() {
	LightData data;
	data.light_direction = this->lightDir;
	data.light_color = this->light_color;
	data.ambient_color = this->ambient_color;
	data.ambient_str = this->ambient_str;
	data.spec_str = this->spec_str;
	data.spec_phong = this->spec_phong;
	data.intensity = this->intensity;

	return data;
}
