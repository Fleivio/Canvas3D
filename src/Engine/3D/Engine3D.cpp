#include "Engine3D.h"

bool Engine3D::render_pistao = true;
bool Engine3D::render_camisa = false;
bool Engine3D::render_biela = true;
bool Engine3D::render_contrapeso = true;
bool Engine3D::pause = false;

Engine3D::Engine3D(){
    this->eng = nullptr;
    angle = 0;
}

Engine3D::Engine3D(Engine *eng, Vector position){
    if(eng == nullptr){
        puts("merda");
        return;
    }
    angle = 0;
    this->eng = eng;
    this->position = position;
    piston = Pistao3d(eng);
    camisa = Camisa3d(eng);
    biela = Biela3d(eng);
    init_contrapeso();
}

Engine3D::Engine3D(Engine *eng, Vector position, double ang) : Engine3D(eng, position){
    set_angle(ang);
}


void Engine3D::update(){
    if(pause) return;
    eng->update();
    piston.update();
    biela.update();
    contrapeso_update();
}

void Engine3D::render(){
    CV3D::translate(position);
    CV3D::rotate({0,0,angle});
    CV3D::scale(2);
        CV3D::color3d(0.8,0,0);
        if(render_camisa) camisa.render();
        if(render_pistao) piston.render();
        if(render_contrapeso) {
            contrapeso1.render();
            contrapeso2.render();
        }
        if(render_biela) biela.render();
        
        auto bidiff = eng->vib->get_position() - eng->pis->bottom_position_cabeca;
        CV3D::color3d(0,1,1);
        CV3D::smallText3d(eng->pis->bottom_position_cabeca + Vector(50, 0, 0), bidiff.mod());

    CV3D::reset_transformations();
}

void Engine3D::set_angle(double ang){
    this->angle = ang;
}

void Engine3D::contrapeso_update(){
    contrapeso1.update();
    contrapeso2.update();
}

void Engine3D::init_contrapeso(){
    contrapeso1 = Contrapeso3d(eng, {}, true);
    contrapeso2 = Contrapeso3d(eng, Vector(0,0,-Contrapeso3d::get_height())/1, false);
}