#pragma once
#include "Light_Point.h"

using namespace light;

Point::Point() {
	this->transform = new Transform();
}

void Point::InitLightData(LightData data) {
	this->light_color = data.light_color;
	this->ambient_color = data.ambient_color;
	this->ambient_str = data.ambient_str;
	this->spec_str = data.spec_str;
	this->spec_phong = data.spec_phong;
	this->intensity = data.intensity;
}

LightData Point::RetrieveLightData() {
	LightData data;
	data.light_position = this->transform->RetrievePosition();
	data.light_color = this->light_color;
	data.ambient_color = this->ambient_color;
	data.ambient_str = this->ambient_str;
	data.spec_str = this->spec_str;
	data.spec_phong = this->spec_phong;
	data.intensity = this->intensity;

	return data;
}

Transform* Point::RetrieveTransform() {
	return this->transform;
}