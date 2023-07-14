#include "Engine.h"
#include <iostream>
#include "../../gl_canvas2d.h"

double Engine::cabeca_altura = 30;
double Engine::raio_pistao = cabeca_altura/2;

Engine::Engine(){}

Engine::Engine(Vector position, bool isUp, double raio, double biela){
    if(biela < raio) biela = raio + 10;
    this->raio = raio;
    this->vib = new Virabrequim(position, isUp ? PI/2 : -PI/2 , raio);
    this->pis = new Pistao({position.x, position.y + biela + cabeca_altura/2}, isUp, raio_pistao, cabeca_altura, raio*2 + cabeca_altura);

    this->biela = biela;
}

double Engine::calc_pistao_y(){
    double a = vib->get_angle() - PI/2;
    double origin = vib->center_position.y;

    return origin + raio * cos(a) + sqrt(biela*biela - raio*raio*sin(a)*sin(a));
}

void Engine::update(){
    this->vib->update();
    auto py = calc_pistao_y();
    this->pis->set_bottom_y(py);
}

void Engine::draw(){
    this->vib->draw();
    this->pis->draw();

    auto pist = pis->bottom_position_cabeca;
    auto vib = this->vib->get_position();
    CV::color(0,0,1);
    CV::line(pist, vib);
}
