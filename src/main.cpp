#include <iostream>
#include <glm/glm.hpp>
#include "myApp.h"
#pragma warning(disable: 4996)
#pragma warning(disable: 4700)



int main()
{

	int width = 1920, height = 1080;

	myApp app("openGl", width, height);

	app.run();


}