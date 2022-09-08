#version 330 core 

out vec4 FragColor;


in vec3 normal;
in vec2 uv;


uniform sampler2D texture_diffuse0;
//uniform sampler2D texture_diffuse1;
//uniform sampler2D texture_diffuse2;
//uniform sampler2D texture_diffuse3;
//
uniform sampler2D texture_specular0;
//uniform sampler2D texture_specular1;
//uniform sampler2D texture_specular2;
//uniform sampler2D texture_specular3;
//


void main()
{
	vec3 finalCol = vec3(0.0);
	
	vec3 diffuse = vec3(0.0), specular = vec3(0.0);

//
	diffuse += texture2D(texture_diffuse0, uv).rgb;

	specular += texture2D(texture_specular0, uv).rgb;
	//diffuse += texture2D(texture_diffuse1, uv).rgb;
//	diffuse += texture2D(texture_diffuse2, uv).rgb;
//	diffuse += texture2D(texture_diffuse3, uv).rgb;
//
//	specular += texture2D(texture_specular0, uv).rgb;
//	specular += texture2D(texture_specular1, uv).rgb;
//	specular += texture2D(texture_specular2, uv).rgb;
//	specular += texture2D(texture_specular3, uv).rgb;
//

	vec3 n = (normal + 1) / 2;
	FragColor =  vec4(diffuse, 1.0);


}