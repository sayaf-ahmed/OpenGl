#version 330 core
#define MAX_DIRECTIONAL_LIGHTS 20
#define MAX_POINT_LIGHTS 20
#define MAX_SPOT_LIGHTS 20

in vec2 uv;

out vec4 FragColor;
uniform vec3 lightCol = vec3(1, 1, 1);

struct material
{
	sampler2D texture_diffuse0;
	sampler2D texture_specular0;
	float shininess;
};

uniform material objMaterial;

void main()
{
	vec3 diff = texture2D(objMaterial.texture_diffuse0, uv).rgb;
	vec3 spec = texture2D(objMaterial.texture_specular0, uv).rgb;
	FragColor = vec4(lightCol, 1.0);
}