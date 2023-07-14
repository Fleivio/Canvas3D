#include "Virabrequim.h"
#include "../../gl_canvas2d.h"
#include "../../Timer/Timer.h"

double Virabrequim::ang_speed = 1;
double Virabrequim::center_rad = 3;


Virabrequim::Virabrequim(Vector position, double act_angle, double radius){
    this->center_position = position;
    this->angle = act_angle;
    this->radius = radius;
}

void Virabrequim::update(){
    this->angle += ang_speed * Timer::get_delta_time();

    if(angle >= 2 * PI)
        angle = angle - 2*PI;
}

double Virabrequim::get_angle(){
    return angle;
}

Vector Virabrequim::get_position(){
    double x = radius * cos(angle);
    double y = radius * sin(angle);

    return center_position + Vector(x, y);
}

Vector Virabrequim::get_opposite_position(){
    double x = radius * cos(angle + PI);
    double y = radius * sin(angle + PI);

    return center_position + Vector(x, y);
}



void Virabrequim::draw(){
    CV::color(0,0,0);

    CV::circle(center_position, radius, 40);
    CV::circleFill(center_position, center_rad, 10);

    CV::color(0,0,1);
    CV::circleFill(get_position(), 3, 10);

    CV::color(1,0,0);
    CV::circle(center_position, radius, 40);
}

double Virabrequim::get_ang_speed(){
    return ang_speed * Timer::get_delta_time();
}

void Virabrequim::inc_speed(){
    ang_speed += 0.1;
}

void Virabrequim::dec_speed(){
    ang_speed -= 0.1;
}
