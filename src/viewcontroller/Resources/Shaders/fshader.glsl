#version 330 core

in vec3 texCoordF;
in vec4 world_posF;
in vec4 world_normalF;
in vec4 eye_positionF;
flat in int activeLightsCountF; 
in vec4 light_positionsF[8];

out vec4 fColor;

uniform int material_shininess;

uniform float material_ke; //emissive koefficient
uniform float material_ka; //ambient koefficient
uniform float material_kd; //diffuse koefficient
uniform float material_ks; //specular koefficient

uniform float att_kC; //constant attenuation 
uniform float att_kL; //linear attenuation 
uniform float att_kQ; //quadratic attenuation 

uniform bool textureEnabled;
uniform bool normalEnabled;
uniform sampler2D texture;
uniform vec3 color;


void main(void)
{
	vec4 fColor_local;
	
	if(textureEnabled) fColor_local = texture2D(texture, texCoordF.st);
	else fColor_local = vec4(color,1);

	if(normalEnabled) 
	{
		float diffuseSum = 0;
		float specularSum = 0;
		float emissive = material_ke;
		float ambient = material_ka;

		for(int i = 0; i < activeLightsCountF; ++i)
		{
			vec4 light_direction = normalize( light_positionsF[i] - world_posF);
			vec4 view_direction = normalize( eye_positionF - world_posF);
			float LDirDotNorm = max(0, dot(light_direction, world_normalF));

			//attenuation
			float d = distance(light_positionsF[i], world_posF);
			float att = 1.0 / (att_kC + d * att_kL + d*d*att_kQ);

			diffuseSum += att * material_kd * LDirDotNorm;
			if(LDirDotNorm > 0.0)
			{
				//Blinn-Phong
				vec4 halfway = normalize(light_direction + view_direction ); 
				specularSum += att * material_ks * pow(max(0, dot(halfway, world_normalF)), material_shininess);
			}
		}

		float lightR = fColor_local.x * (emissive + ambient + diffuseSum + specularSum);
		float lightG = fColor_local.y * (emissive + ambient + diffuseSum + specularSum);
		float lightB = fColor_local.z * (emissive + ambient + diffuseSum + specularSum);
		
		fColor = vec4(lightR,lightG,lightB,1);
		
	}
	else fColor = fColor_local;
}


