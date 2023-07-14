#include "3dEngineParts.h"

double Contrapeso3d::contrapeso_h = 5; 
double Contrapeso3d::contrapeso_r = 20; 
double Contrapeso3d::contrapeso_dist = 10; 

double Camisa3d::camisa_r = 3;

Contrapeso3d::Contrapeso3d(Engine* eng, Vector globalPos, bool isUp){
    double dist = isUp ? contrapeso_dist : -contrapeso_dist;
    Vector op = eng->vib->get_opposite_position();
    Vector pos = eng->vib->get_position();

    contraGrande = MeshGenerator::genCilinder( {}, contrapeso_h, contrapeso_r);
    contraGrande.mapTransform(
        Matrix::translate( globalPos + op + Vector(0,0, dist)/1 ) );

    contraPequeno = MeshGenerator::genCilinder( {}, contrapeso_h, contrapeso_r/2);
    contraPequeno.mapTransform(
        Matrix::translate( globalPos + pos + Vector(0,0, dist)/1 ) );
    
    liga1 = MeshGenerator::genPlane(
        op + Vector(-contrapeso_r, 0, dist)/1,
        op + Vector(-contrapeso_r, 0, dist + contrapeso_h)/1,
        pos + Vector(-contrapeso_r/2, 0, dist + contrapeso_h)/1,
        pos + Vector(-contrapeso_r/2, 0, dist)/1
    );
    liga1.mapTransform( Matrix::translate(globalPos) );

    liga2 = MeshGenerator::genPlane(
        op + Vector(contrapeso_r, 0, dist)/1,
        op + Vector(contrapeso_r, 0, dist + contrapeso_h)/1,
        pos + Vector(contrapeso_r/2, 0, dist + contrapeso_h)/1,
        pos + Vector(contrapeso_r/2, 0, dist)/1
    );
    liga2.mapTransform( Matrix::translate(globalPos) );
}

void Contrapeso3d::update(){
    contraGrande.mapTransform( Matrix::rotationZ(Virabrequim::get_ang_speed()) );
    contraPequeno.mapTransform( Matrix::rotationZ(Virabrequim::get_ang_speed()) );
    liga1.mapTransform( Matrix::rotationZ(Virabrequim::get_ang_speed()) );
    liga2.mapTransform( Matrix::rotationZ(Virabrequim::get_ang_speed()) );
}

void Contrapeso3d::render(){
    CV::color(1,1,1);
    contraGrande.render();
    contraPequeno.render();
    liga1.render();
    liga2.render();
}

double Contrapeso3d::get_height(){
    return contrapeso_h;
}

double Contrapeso3d::get_radius(){
    return contrapeso_r;
}

double Contrapeso3d::get_dist(){
    return contrapeso_dist;
}

Pistao3d::Pistao3d(Engine *eng){
    this->eng = eng;
    piston = MeshGenerator::genCilinder( {}, eng->cabeca_altura, eng->raio_pistao);
    piston.mapTransform( Matrix::rotationX(-PI/2));
    piston.mapTransform( Matrix::translate( eng->pis->bottom_position_cabeca / 1 ) );
    piston_last_position = eng->pis->bottom_position_cabeca;
}

void Pistao3d::update(){
    Vector newPos = eng->pis->bottom_position_cabeca;
    piston.mapTransform( Matrix::translate(newPos - piston_last_position) );
    piston_last_position = newPos;
}

void Pistao3d::render(){
    CV::color(1,0,0);
    piston.render();
}

Camisa3d::Camisa3d(Engine *eng){
    camisa = MeshGenerator::genHollowCilinder( {}, eng->pis->altura_cilindro, eng->raio_pistao + 1, camisa_r);
    camisa.mapTransform( Matrix::rotationX(-PI/2));

    Vector min_center = eng->pis->get_bottom_right_position() / 1 + Vector(-eng->raio_pistao, 0) / 1;
    camisa.mapTransform( Matrix::translate( min_center / 1 ) );
}

void Camisa3d::render(){
    CV::color(1,1,1);
    camisa.render();
}

Biela3d::Biela3d(Engine *eng){
    this->eng = eng;
    double thickness = Contrapeso3d::get_dist() * 2;
    auto vib = eng->vib;

    conexao = MeshGenerator::genCilinder( {}, thickness, 10);
    conexao.mapTransform( Matrix::translate( vib->get_position() + Vector(0,0, - thickness/2) ) );

    pinoPonta = MeshGenerator::genHollowCilinder( {}, 4, 12, 2);
    pinoPonta.mapTransform( Matrix::translate( vib->get_position() + Vector(0,0, -2) / 1 ) );

    pino = MeshGenerator::genCilinder( {vib->get_position().x, 0, vib->get_position().y},
                                        {eng->pis->bottom_position_cabeca.x, 0, eng->pis->bottom_position_cabeca.y}, 4);
    pino.mapTransform(Matrix::rotationX(-PI/2));
    // pino.mapTransform( Matrix::translate( eng->vib->get_position()) );
}

void Biela3d::render(){
    CV::color(1,1,1);
    conexao.render();
    CV::color(1,0,0);
    pinoPonta.render();
    pino.render();
}

void Biela3d::update(){
    auto vib = eng->vib;

    conexao.mapTransform( Matrix::rotationZ(Virabrequim::get_ang_speed()) );
    pinoPonta.mapTransform( Matrix::rotationZ(Virabrequim::get_ang_speed()) );
    pino = MeshGenerator::genCilinder( {vib->get_position().x, 0, vib->get_position().y},
                                        {eng->pis->bottom_position_cabeca.x, 0, eng->pis->bottom_position_cabeca.y}, 4);
    pino.mapTransform(Matrix::rotationX(-PI/2));

}