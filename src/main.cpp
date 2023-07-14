#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include "gl_canvas2d.h"

int mouseX, mouseY;

#include "Timer/Timer.h"
#include "Engine/EngineGroup.h"
#include "gl_canvas3d.h"
#include "Demos.h"
#include "Input.h"

bool drawDemos = false;
double angle = PI/4;

void render3d(){
	CV::translate(CV3D::screenWidth/2, CV3D::screenHeight/2);
	CV3D::draw_coordinate_system();
	CV3D::draw_info();
	CV3D::draw_coord_nums();

	if(!drawDemos) EngineGroup::render();
	else Demos::render_demos();
	CV::translate(0,0);
}


void keyboard(int key)
{
	Input::keyboard_down(key);
}

void keyboardUp(int key)
{
	Input::keyboard_up(key);
	if(key == 'f') drawDemos = !drawDemos;

}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
	mouseX = x;
	mouseY = y;

	Input::att_mouse(button, state, x, y);

	if(wheel == 0) Input::mouse_wheel(direction);
}


void render()
{
	Timer::update();
	CV::clear(0,0,0);
	Input::update();
	render3d();
	Timer::wait_fps();
}

int main(void)
{
	srand(time(nullptr));
	Timer::init();
	Demos::init_demos();
	EngineGroup::init();

   	CV::init(&(CV3D::screenWidth), &(CV3D::screenHeight), "Clash Royale");
   	CV::run();
}
