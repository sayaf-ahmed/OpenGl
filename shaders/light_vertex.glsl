#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;


uniform float boarderThikness = 0.01;


uniform mat4x4 projMat = mat4(1.0);
uniform mat4x4 modelMat= mat4(1.0);
uniform mat4x4 viewMat = mat4(1.0);

out vec2 uv;



void main()
{
   gl_Position = projMat * viewMat * modelMat * vec4(aPos + (normalize(aNormal) * boarderThikness), 1.0);
   uv = aUv;
}