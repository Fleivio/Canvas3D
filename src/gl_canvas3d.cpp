#include "gl_canvas3d.h"

#include "gl_canvas2d.h"
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

MatrixStack CV3D::transformations = MatrixStack(); 
Mode CV3D::mode = WIREFRAME;
PerspecCamera CV3D::pCamera = PerspecCamera(Vector(300, 300, 300), Vector(0, 0, 0), Vector(0, 1, 0), -200);
OrthoCamera CV3D::oCamera = OrthoCamera(Vector(300, 300, 300), Vector(0, 0, 0), Vector(0, 1, 0));
Camera *CV3D::camera = &pCamera;
CameraMode CV3D::camera_mode = PERSPECTIVE;
int CV3D::screenWidth = 854;
int CV3D::screenHeight = 480;

double CV3D::axis_size = 300;
double CV3D::info_distance = 400;

void CV3D::set_camera(Camera *camera) {
    CV3D::camera = camera;
}

void CV3D::set_cam_mode(CameraMode m) {
    if(camera_mode == m) return;
    camera_mode = m;
    switch(m){
        case PERSPECTIVE:
            pCamera.set(camera);
            set_camera(&pCamera);
            break;
        case ORTHOGRAPHIC:
            oCamera.set(camera);
            set_camera(&oCamera);
            break;
    }
}

void CV3D::stack_up_transformations(double transformation[4][4]) {
    Matrix m = Matrix(transformation);
    stack_up_transformations(m);
}

void CV3D::stack_up_transformations(Matrix m) {
    transformations.stack_up(m);
}

void CV3D::reset_transformations() {
    transformations.reset();
}

void CV3D::translate(Vector v) {
    stack_up_transformations( Matrix::translate(v) );
}

void CV3D::scale(Vector v) {
    stack_up_transformations( Matrix::scale({v}) );
}

void CV3D::scale(double factor) {
    stack_up_transformations( Matrix::scale(factor) );
}

void CV3D::rotate(Vector v) {
    stack_up_transformations( Matrix::rotation({v}) );
}

void CV3D::draw_coordinate_system(){
    CV::color(1,0,0);
    CV3D::line3d(Vector(-axis_size, 0, 0), Vector(axis_size, 0, 0));

    CV::color(0,1,0);
    CV3D::line3d(Vector(0, -axis_size, 0), Vector(0, axis_size, 0));

    CV::color(0,0,1);
    CV3D::line3d(Vector(0, 0, -axis_size), Vector(0, 0, axis_size));
}

void CV3D::draw_info(){
    CV::color(1,0,0);
    text3d({info_distance,0,0}, "x");

    CV::color(0,1,0);
    text3d({0,info_distance,0}, "y");
    
    CV::color(0,0,1);
    text3d({0,0,info_distance}, "z");
}

double round_10(double valor) {
    if (valor == 0)
        return 0;
    
    double expoente = floor(log10(valor < 0 ? -valor : valor));
    double fator_escala = pow(10, expoente);
    double valor_arredondado = round(valor / fator_escala);
    if (valor_arredondado == 10) {
        valor_arredondado = 1;
        expoente += 1;
    }
    return copysign(pow(10, expoente), valor_arredondado);
}

void CV3D::draw_coord_nums(){
    double cam_distance = camera->position.mod();
    double step = round_10(cam_distance) * 10;

    CV::color(1,0,0);
    for(double i = -axis_size; i <= axis_size; i += step){
        if(i == 0) continue;
        text3d({i,0,0}, to_string((int)i).c_str());
    }

    CV::color(0,1,0);
    for(double i = -axis_size; i <= axis_size; i += step){
        if(i == 0) continue;
        text3d({0,i,0}, to_string((int)i).c_str());
    }

    CV::color(0,0,1);
    for(double i = -axis_size; i <= axis_size; i += step){
        if(i == 0) continue;
        text3d({0,0,i}, to_string((int)i).c_str());
    }
}

void CV3D::text3d(Vector v, const char *t){
    CV::text(transform(v), t);
}

void CV3D::text3d(Vector v, int n){
    const char *t = to_string(n).c_str();
    CV3D::text3d(v, t);
}

void CV3D::text3d(Vector v, double n){
    const char *t = to_string(n).c_str();
    CV3D::text3d(v, t);
}

void CV3D::text3d(Vector v, float n){
    const char *t = to_string(n).c_str();
    CV3D::text3d(v, t);
}

void CV3D::smallText3d(Vector v, const char *t){
    CV::small_text(transform(v), t);
}

void CV3D::smallText3d(Vector v, int n){
    const char *t = to_string(n).c_str();
    CV3D::smallText3d(v, t);
}

void CV3D::smallText3d(Vector v, double n){
    const char *t = to_string(n).c_str();
    CV3D::smallText3d(v, t);
}

void CV3D::smallText3d(Vector v, float n){
    const char *t = to_string(n).c_str();
    CV3D::smallText3d(v, t);
}

Vector CV3D::transform(Vector v) {
    return camera->project( transformations.apply(v) );
}

void CV3D::color3d(float r, float g, float b){
    CV::color(r, g, b);
}

void CV3D::color3d(float r, float g, float b, float a){
    CV::color(r, g, b, a);
}

void CV3D::line3d(Vector v1, Vector v2){
    Vector v1_transformed = transform(v1);
    Vector v2_transformed = transform(v2);

    CV::line(v1_transformed, v2_transformed);
}

void CV3D::point3d(Vector v){
    glPointSize(5);
    Vector v_transformed = transform(v);

    CV::point(v_transformed);
}

void CV3D::triangle3d(Vector v1, Vector v2, Vector v3){
    Vector lst_vec[3] = {
        v1, v2, v3
    };
    
    CV3D::polygon3d(lst_vec, 3);
}

void CV3D::quad3d(Vector v1, Vector v2, Vector v3, Vector v4){
    Vector lst_vec[4] = {
        v1, v2, v3, v4
    };
    
    CV3D::polygon3d(lst_vec, 4);
}

void CV3D::polygon3d(Vector *vertices, int n_vertices){
    Vector *vertices_transformed = new Vector[n_vertices];
    for(int i = 0; i < n_vertices; i++){
        vertices_transformed[i] = transform(vertices[i]);
    }

    if (mode == WIREFRAME)
        CV::polygon(vertices_transformed, n_vertices);
    else
        CV::polygonFill(vertices_transformed, n_vertices);
}

void CV3D::set_mode(Mode m){
    CV3D::mode = m;
}