#version 330 core

in vec3 normal;
in vec3 uv;



out vec4 fragCol;



uniform samplerCube skyBox;

void main()
{


	fragCol = textureCube(skyBox, uv);

//	fragCol = vec4(1, 1, 1, 1);

}
