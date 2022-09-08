#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;



uniform mat4x4 projMat = mat4(1.0);
uniform mat4x4 modelMat= mat4(1.0);
uniform mat4x4 viewMat = mat4(1.0);

out vec2 uv;
out vec3 normal;
out vec3 fragPos;



void main()
{
   gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0);
   uv = aUv;
   fragPos = vec3(modelMat * vec4(aPos, 1.0));
   normal = mat3(inverse(transpose(modelMat))) * aNormal;
}