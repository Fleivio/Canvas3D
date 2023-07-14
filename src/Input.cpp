#include "Input.h"

#include "gl_canvas3d.h"
#include "Engine/3D/Engine3D.h"
#include "Engine/2D/ViraBrequim.h"

#include <algorithm>
#include <iostream>

Vector Input::previousPosition = Vector();
Vector Input::actualPosition = Vector();
Vector Input::movementDelta = Vector();
MouseState Input::state = HOVER;
list<int> Input::keysDown = list<int>();

void Input::att_mouse(int button, int currentAction, int x, int y)
{
    if (button == RIGHT_BUTTON) return;

    previousPosition.set(actualPosition);
    actualPosition.set(x, y);
    att_movement_delta();

    calc_next_state(currentAction);
    handle_action();
}

void Input::calc_next_state(int currentAction)
{
    switch (currentAction)
    {
    case MOUSE_DOWN:
        if (state == HOVER || state == CLICK_UP || state == UN_HOLD)
        {
            state = CLICK_DOWN;
        }
        break;
    case MOUSE_MOVE:
        if (state == CLICK_DOWN)
        {
            state = HOLD;
        }
        else if (state == UN_HOLD || state == CLICK_UP)
        {
            state = HOVER;
        }
        break;
    case MOUSE_UP:
        if (state == HOLD)
        {
            state = UN_HOLD;
        }
        else if (state == CLICK_DOWN)
        {
            state = CLICK_UP;
        }
        break;
    }
}

void Input::handle_action()
{
    switch (state)
    {
    case CLICK_DOWN:
        // não precisei
        break;
    case CLICK_UP:
        // não precisei
        break;
    case HOVER:
        // não precisei
        break;
    case HOLD:
        // CV3D::camera->rotate_camera(movementDelta * (-0.01));
        break;
    case UN_HOLD:
        // não precisei
        break;
    }
}

void Input::att_movement_delta()
{
    movementDelta.x = actualPosition.x - previousPosition.x;
    movementDelta.y = actualPosition.y - previousPosition.y;
}

void Input::keyboard_down(int key)
{
    if( find(keysDown.begin(), keysDown.end(), key) != keysDown.end() ) return;
    keysDown.push_back(key);
}

void Input::keyboard_up(int key)
{
    keysDown.remove(key);
    switch (key)
	{
        case 'p':
            Engine3D::pause = !Engine3D::pause;
            break;
        case '1':
            Engine3D::render_pistao = !Engine3D::render_pistao;
            break;
        case '2':
            Engine3D::render_camisa = !Engine3D::render_camisa;
            break;
        case '3':
            Engine3D::render_biela = !Engine3D::render_biela;
            break;
        case '4':
            Engine3D::render_contrapeso = !Engine3D::render_contrapeso;
            break;
        case 'i':
            CV3D::set_cam_mode(PERSPECTIVE);
            break;
        case 'o':
            CV3D::set_cam_mode(ORTHOGRAPHIC);
            break;
    }
}

void Input::mouse_wheel(int direction)
{
    if(direction == 1)
        CV3D::camera->zoom_in();
    else
        CV3D::camera->zoom_out();
}

void Input::update(){

    for (auto key : keysDown)
    {
        switch ( key )
        {
        case 'q':
            CV3D::camera->rotate_camera({0,0,0.04});
            break;
        case 'e':
            CV3D::camera->rotate_camera({0,0,-0.04});
            break;
        case 'a':
            CV3D::camera->rotate_camera({0,0.04,0});
            break;
        case 'd':
            CV3D::camera->rotate_camera({0,-0.04,0});
            break;
        case 'w':
            CV3D::camera->rotate_camera({0.04,0,0});
            break;
        case 's':
            CV3D::camera->rotate_camera({-0.04,0,0});
            break;
        case '=':
        case '+':
            Virabrequim::inc_speed();
            break;
        case '-':
            Virabrequim::dec_speed();
            break;
        default:
            break;
        }
    }
}
