#include <chrono>
#include "program.h"
#include "glfwinc.h"
#include <iostream>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>
program::program()
	:m_width(0), m_height(0), input(nullptr)
{

}

program::program(const char* title, int width, int height)
{

	m_width = width; 
	m_height = height;
	m_win.create(title, width, height);
	//glfwSetInputMode(m_win.m_win, GLFW_CURSOR_DISABLED, GLFW_TRUE);
	input = inputManager::getInstance();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_win.m_win, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	glfwSetKeyCallback(m_win.m_win, inputManager::key_callback);
	glfwSetCursorPosCallback(m_win.m_win, inputManager::cursor_position_callback);
	glfwSetMouseButtonCallback(m_win.m_win, inputManager::mouse_button_callback);
}

void program::run()
{
	create();
	update();
}

void program::enableVsync(bool enable) 
{
	m_win.enableVsync(enable);
}

void program::grabMouse(bool grab)
{
	m_win.confineCursor(grab);
}

program::~program()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	//delete input;
}

void program::update()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	auto stPoint = std::chrono::high_resolution_clock::now();
	auto edPoint = std::chrono::high_resolution_clock::now();
	while (m_win.getIsOpen())
	{
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		stPoint = edPoint;
		edPoint = std::chrono::high_resolution_clock::now();

		float dt = std::chrono::duration<float>(edPoint - stPoint).count();

		onUserUpdate(dt);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		m_win.swapBuffers();
		//input->clearKeys();
	}
}

void program::create()
{
	onUserCreate();
}
