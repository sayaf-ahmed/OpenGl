#pragma warning (disable : 4996)
#include <iostream>
#include "myApp.h"
#include "core/vertexAttributeList.h"
#include <glm/gtc/matrix_transform.hpp>
#include <stbi_image.h>

struct tex
{

	unsigned char* data;
	int width, height, channels;

	tex(const char* path, bool flip)
	{
		stbi_set_flip_vertically_on_load(false);
		data = stbi_load(path, &width, &height, &channels, 3);

		if (data == NULL)
			std::cout << "failed to load " << path << "\b";
	}
};

void myApp::onUserCreate()
{
	glDepthFunc(GL_LEQUAL);
	int glMajor = 0, glMinor;

	glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
	glGetIntegerv(GL_MINOR_VERSION, &glMinor);

	std::cout << "using opengl version: " << glMajor << "." << glMinor << "\n";

	mainCam.setPosition({ 0, 0, 4 });
	mainCont.cam = &mainCam;
	enableVsync(true);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




	tex textures[6] =
	{
		tex("images/cubeMap/right.jpg", 1),
		tex("images/cubeMap/left.jpg", 1),
		tex("images/cubeMap/top.jpg", 1),
		tex("images/cubeMap/bottom.jpg", 1),
		tex("images/cubeMap/front.jpg", 1),
		tex("images/cubeMap/back.jpg", 1),
	};



	glGenTextures(1, &cubeMabTex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMabTex);

	for(int i =0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textures[i].width, textures[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, textures[i].data);
	}


	for (int i = 0; i < 6; i++)
	{
		stbi_image_free(textures[i].data);

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	vs.load("shaders/cubeMap/cube.vert", shaderType::vertex);
	fs.load("shaders/cubeMap/cube.frag", shaderType::fragment);

	cubeMapShader.loadMin(vs, fs);

	vs.destroy();
	fs.destroy();

	vs.load("shaders/basic_vert.glsl", shaderType::vertex);
	fs.load("shaders/basic_frag.glsl", shaderType::fragment);


	basic.loadMin(vs, fs);
	bag.setShader(&basic);
	bag.setModel(&bagMod);


	




	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);


	box.setModel(&boxMod);
	box.setShader(&cubeMapShader);

	
}

void myApp::onUserUpdate(float dt)
{

	glm::vec3 camPos = mainCam.getPos();
	glEnable(GL_DEPTH_TEST);
;	glViewport(0, 0, m_width, m_height);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(input->getKeyReleased(keys::KEY_ESCAPE))
		conf = !conf;

	if(conf)
		mainCont.update(dt);

	grabMouse(conf);


	
	glm::mat4x4 projMat = glm::perspective(glm::radians(45.0f), (float)m_width / m_height, 0.001f, 10000.0f);
	glm::mat4x4 viewMat = mainCam.getView();

	cubeMapShader.setUniformMat4x4("projMat", projMat);
	cubeMapShader.setUniformMat4x4("viewMat", glm::mat4x4(glm::mat3x3(viewMat)));
	

	glm::mat4x4 skyBoxScale = glm::scale(glm::mat4x4(1.0), { 0.1, 0.1, 0.1 });
	
	cubeMapShader.setUniformMat4x4("modelMat", skyBoxScale);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMabTex);

	//cubeMapShader.setUniform1i("skyBox", 0);

	box.draw();



	basic.setUniformMat4x4("projMat", projMat);
	basic.setUniformMat4x4("viewMat", viewMat);
	basic.setUniform3f("viewPos", mainCam.getPos());

	bag.draw();


	ImGui::Begin("frameInfo");

	ImGui::Text("frameTime: %f ms", dt);
	ImGui::Text("fps: %f", 1 / dt);
	ImGui::Text("camPosition: x:%f, y:%f, z:%f", camPos.x, camPos.y, camPos.z);
	ImGui::Text("camFront: x:%f, y:%f, z:%f", mainCont.front.x, mainCont.front.y, mainCont.front.z);
	
	ImGui::End();


	time += dt;
}

myApp::~myApp()
{
	glDeleteTextures(1, &cubeMabTex);
}
