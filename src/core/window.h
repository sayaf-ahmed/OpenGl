#pragma once
#include "glfwinc.h"
class window
{
private:
	GLFWwindow* m_win;
	int m_width, m_height;
	const char* m_title;
	bool m_isOpen = true;
public:
	window();
	window(const char* title, int width, int height);

	bool create(const char* title, int width, int height);

	void enableVsync(bool enable);

	void confineCursor(bool confine);
	void close();
	void swapBuffers() const;

	int getWidth() const;
	int getHeight() const;

	bool getIsOpen() const;

	~window();

	friend class program;
};
