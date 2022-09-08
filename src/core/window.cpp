#include "window.h"
#include <iostream>
#include <glad/glad.h>


window::window()
	:m_width(0), m_height(0), m_title(0), m_win(NULL)
{
}

window::window(const char* title, int width, int height)
{
	create(title, width, height);
}

bool window::create(const char* title, int width, int height)
{
	m_width = width;
	m_height = height;
	m_title = title;
	if (!glfwInit())
	{
		const char* err;
		glfwGetError(&err);
		std::cout << "error initializing glfw:" << err << "\n";
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	m_win = glfwCreateWindow(width, height, m_title, NULL, NULL);


	if (!m_win)
	{
		const char* err;
		glfwGetError(&err);

		std::cout << "error creating window :" << err;
		return 0;
	}
	glfwMakeContextCurrent(m_win);



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "error loading openGl";
		return 0;
	}


	//SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	return true;

}

void window::enableVsync(bool enable)
{
	glfwSwapInterval(enable);
}

void window::confineCursor(bool confine)
{
	if(confine)
		glfwSetInputMode(m_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else 
		glfwSetInputMode(m_win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		//glfwSetInputMode(m_win, GLFW_CURSOR_HIDDEN, confine);
}

void window::close()
{
	m_isOpen = false;
}

void window::swapBuffers() const
{
	glfwSwapBuffers(m_win);
}

int window::getWidth() const
{
	return m_width;
}

int window::getHeight() const
{
	return m_height;
}

bool window::getIsOpen() const
{
	return !glfwWindowShouldClose(m_win);
}

window::~window()
{
	glfwDestroyWindow(m_win);
}
