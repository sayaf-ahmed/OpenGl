#version 330 core


in vec2 uv;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;
uniform vec3 lightCol = vec3(1, 1, 1);

struct material
{
	sampler2D texture_diffuse0;
	sampler2D texture_specular0;
	float shininess;
};

uniform material objMaterial;
uniform vec3 viewPos;

uniform samplerCube skybox;

float t  = 0.3;
void main()
{

	vec3 diff = texture2D(objMaterial.texture_diffuse0, uv).rgb;
	vec3 spec = texture2D(objMaterial.texture_specular0, uv).rgb;

	vec3 I = normalize(fragPos - viewPos);
	vec3 R = normalize(reflect(I, normal));
	
	float ratio = 1/ 1.52;

	vec3 RR = refract(I, normalize(normal), 0.658);

	//finalCol = vec4(finalCol.rgb + diff, 1.0);

	//float col = (diff.r + diff.g + diff.b)/3.0;
	//FragColor = vec4(diff, 1.0);//vec4(vec3(col), 1.0);
	vec4 reflection =  texture(skybox, RR);
	FragColor = reflection * t + vec4(diff * (1-t), 1.0);
}