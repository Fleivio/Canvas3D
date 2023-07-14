#include "Pistao.h"
#include "../../gl_canvas2d.h"

Pistao::Pistao(Vector position, bool isUp, double raio, double altura_cabeca, double altura_cilindro){
    this->center_position = position;
    this->raio = raio;
    this->altura_cabeca = altura_cabeca;
    this->altura_cilindro = altura_cilindro;
    this->var_range = altura_cilindro - altura_cabeca;

    set_is_up(isUp);
}

Vector Pistao::get_top_left_position(){
    return center_position + Vector( -raio, altura_cilindro/2);
}

Vector Pistao::get_bottom_right_position(){
    return center_position + Vector( raio, -altura_cilindro/2);
}

void Pistao::set_is_up(bool isUp){
    if(isUp){
        this->bottom_position_cabeca = get_top_left_position() + Vector( raio , -altura_cabeca);
    }else{
        this->bottom_position_cabeca = get_bottom_right_position() + Vector( -raio , 0);
    }
}

void Pistao::set_bottom_y(double y){
    this->bottom_position_cabeca.y = y;
}

void Pistao::draw(){
    //cilindro
    CV::color(0,0.1,0);
    CV::rect(get_top_left_position(), get_bottom_right_position());

    //cabeça
    CV::color(1,0,0);
    CV::rect( bottom_position_cabeca.x - raio , bottom_position_cabeca.y,
                  bottom_position_cabeca.x + raio, bottom_position_cabeca.y + altura_cabeca);

    //ponto central
    CV::color(1,0,0);
    CV::circle(center_position, 3, 10);

    //ponto da cabeça
    CV::color(0,0,1);
    CV::circle(bottom_position_cabeca, 3, 10);
}
