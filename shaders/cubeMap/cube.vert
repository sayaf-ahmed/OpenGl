#version 330 core


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;


out vec3 normal;
out vec3 uv;

uniform mat4 modelMat = mat4(1.0);
uniform mat4 viewMat = mat4(1.0);
uniform mat4 projMat = mat4(1.0);






void main()
{
	vec4 pos = projMat * viewMat * modelMat * vec4(aPos, 1.0);
	gl_Position = pos.xyww;

	normal = inverse(transpose(mat3(modelMat))) * aNormal;

	uv  = aPos;
}