#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 texCoord;
layout(location = 2) in vec3 normal;

out vec3 texCoordF;
out vec4 world_posF;
out vec4 world_normalF;
out vec4 eye_positionF;
flat out int activeLightsCountF; 
out vec4 light_positionsF[8];

uniform int activeLightsCount; 
uniform vec4 light_positions[8];
uniform vec4 eye_position;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;


void main(void)
{
	gl_PointSize = 2.0;
	mat4 modelViewMatrix = viewMatrix * modelMatrix;

	eye_positionF = eye_position;

	activeLightsCountF = activeLightsCount > 8 ? 8 : activeLightsCount;
	for(int i=0;i<8;++i) light_positionsF[i] = viewMatrix*light_positions[i];

	texCoordF = texCoord;
	world_posF = modelViewMatrix * vec4(vertex, 1.0);
	world_normalF = normalize(modelViewMatrix * vec4(normal, 0.0));
	gl_Position = projectionMatrix * modelViewMatrix * vec4(vertex, 1.0);
}