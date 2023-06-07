#version 330 core

uniform vec3 objColor;
out vec4 FragColor; //Color pixel

void main(){
	
	//FragColor = vec4(0.0f, 0.5f, 0.7f, 1.0f);
	FragColor.rgb = objColor;
	FragColor.a = 1.0f;
}