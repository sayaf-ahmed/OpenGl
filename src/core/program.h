#pragma once
#include "window.h"
#include "inputManager.h"
#include "imgui/imgui.h"
class program
{
private:
	window m_win;

protected:
	int m_width, m_height;
public:


	program();
	program(const char* title, int width, int height);

	inputManager* input;
	
	void run();

	virtual void onUserCreate() = 0;
	virtual void onUserUpdate(float dt) = 0;

	void enableVsync(bool enable);

	void grabMouse(bool grab);

	virtual ~program();

private:
	void update();
	void create();

};

