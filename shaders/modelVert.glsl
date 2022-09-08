#version 330 core

layout(location = 0 ) in vec3 aPos;
layout(location = 1 ) in vec3 aNor;
layout(location = 2 ) in vec2 aUV;



uniform mat4x4 modelMat = mat4(1.0);
uniform mat4x4 viewMat = mat4(1.0);
uniform mat4x4 projMat = mat4(1.0);

out vec3 normal;
out vec2 uv;
out vec3 fragpos;

void main()
{

	gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0);

	normal = (inverse(transpose(mat3x3(modelMat))) * aNor);
	uv = aUV;
	fragpos = aPos;
}