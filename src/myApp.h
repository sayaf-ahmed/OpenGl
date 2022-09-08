#pragma once
#define M_PI 3.1415926
#include "core/program.h"
#include "resources/shader.h"
#include "core/bufferObject.h"
#include "core/vertexArray.h"
#include "imgui/imgui.h"

#include <glad/glad.h>
#include <cstdio>
#include "resources/texture.h"
#include "resources/cam3d.h"
#include "resources/light.h"
#include <glm/glm.hpp>
#include "resources/material.h"
#include "resources/pointLight.h"

#include "resources/directionalLight.h"
#include "resources/spotLight.h"
#include "resources/model.h"
#include "object.h"

class myApp : public program
{
private:
	float time = 0;
	const char* title = "openGl test";
	
	
	shaderUnit vs, fs;
	shader cubeMapShader = shader("cubeMapShader"), basic = shader("basicShader");

	model bagMod = model("models/bag/backpack.obj"), 
		  boxMod = model("models/box.obj");


	cam3d mainCam;
	
	object box;

	unsigned int cubeMabTex;
	object bag;


	struct fpsCont
	{
		glm::vec3 target = { 0, 0, -1 };
		glm::vec3 front = { 0, 0, 1 };
		glm::vec3 right = { 1, 0, 0 };
		glm::vec3 up = { 0, 1, 0 };
		cam3d* cam = nullptr;
		int lastX = 0, lastY = 0;

		float speed = 1;

		float yaw = -90, pitch = 0;
		bool firstMouse = true;

		inputManager* input = inputManager::getInstance();


		void update(float dt)
		{
			updatePosition(dt);
			updateFront();
		}

		void updateFront()
		{
			auto [mX, mY] = input->getMouse();

			if (firstMouse)
			{
				lastX = mX;
				lastY = mY;
				firstMouse = false;
			}

	
			float xoffset = mX - lastX;
			float yoffset = lastY - mY;
			lastX = mX;
			lastY = mY;

			float sensitivity = 0.1f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			//std::cout << "pitch: " << pitch << "\n";
			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			front = glm::normalize(direction);


			right = glm::normalize(glm::cross(front, up));

			//right = glm::cross(up, front);
			//std::cout << "target: (" << target.x << ", " << target.y << ", " << target.z << ")" << "\n";
			
			
			
			//calculateMatrix();
			cam->setTarget(cam->getPos() + front);
		}

		void updatePosition(float dt)
		{
			if (input->getKeyPressed(keys::KEY_LEFT_SHIFT))
				speed = 10;
			else
				speed = 1;
			glm::vec3 camPos = cam->getPos();
			if (input->getKeyPressed(keys::KEY_W))
			{
				camPos = camPos + front * dt * speed;
				cam->setPosition(camPos);
			}
			if (input->getKeyPressed(keys::KEY_S))
			{
				camPos = camPos - front * dt * speed;
				cam->setPosition(camPos);
			};

			if (input->getKeyPressed(keys::KEY_A))
			{
				camPos = camPos - right * dt * speed;
				cam->setPosition(camPos);
			}
			if (input->getKeyPressed(keys::KEY_D))
			{
				camPos = camPos + right * dt * speed;
				cam->setPosition(camPos);
			};

			if (input->getKeyPressed(keys::KEY_E))
			{
				camPos = camPos + up * dt * speed;
				cam->setPosition(camPos);
			};

			if (input->getKeyPressed(keys::KEY_Q))
			{
				camPos = camPos - up * dt * speed;
				cam->setPosition(camPos);
			};

		}

		void calculateMatrix()
		{
			glm::vec3 camPos = cam->getPos();
			//glm::vec3 target = camPos + front;
			//target = glm::normalize(target);


			front = glm::normalize((target + camPos) - camPos);
			right = normalize(glm::cross(up, front));
			up = normalize(glm::cross(target, right));


		}
	} mainCont;


	bool conf = false;
public:
	myApp(const char* title, int width, int height)
		:program(title, width, height){}

	void onUserCreate() override;

	virtual void onUserUpdate(float dt) override;

	glm::mat4x4 setUpRotationMatrix(float angle, glm::vec3 axis)
	{
		glm::mat4x4 rotationMatrix;
		float u = axis.x, v = axis.y, w = axis.z;
		float L = (u * u + v * v + w * w);
		angle = angle * M_PI / 180.0; //converting to radian value
		float u2 = u * u;
		float v2 = v * v;
		float w2 = w * w;
		rotationMatrix[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
		rotationMatrix[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
		rotationMatrix[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;
		rotationMatrix[0][3] = 0.0;
		rotationMatrix[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
		rotationMatrix[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
		rotationMatrix[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;
		rotationMatrix[1][3] = 0.0;
		rotationMatrix[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
		rotationMatrix[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
		rotationMatrix[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;
		rotationMatrix[2][3] = 0.0;
		rotationMatrix[3][0] = 0.0;
		rotationMatrix[3][1] = 0.0;
		rotationMatrix[3][2] = 0.0;
		rotationMatrix[3][3] = 1.0;

		return rotationMatrix;
	}

	static void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		std::cout << "---------------" << std::endl;
		std::cout << "Debug message (" << id << "): " << message << std::endl;

		switch (source)
		{
		case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
		} std::cout << std::endl;

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
		} std::cout << std::endl;

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
		} std::cout << std::endl;
		std::cout << std::endl;
	}

	~myApp();
};


