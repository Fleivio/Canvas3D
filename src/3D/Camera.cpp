#include "Camera.h"

Camera::Camera(Vector position, Vector aimPosition, Vector up){
    this->position = position;
    this->aimPosition = aimPosition;
    this->up = up;
}

Camera::Camera(){
    position = Vector(0,0,0);
    aimPosition = Vector(0,0,0);
    up = Vector(0,1,0);
}

Vector Camera::get_direction(){
    return (aimPosition - position).normalize();
}

void Camera::rotate_camera(Vector v){
    map_transformation(Matrix::rotation(v));
}

void Camera::map_transformation(Matrix m){
    position = m * position;
    up = m * up;
}

void Camera::zoom_in(){
    auto dir = get_direction().mod() == 0 ? Vector(0,0,1) : get_direction();
    position = position + dir * 10;
}

void Camera::zoom_out(){
    auto dir = get_direction().mod() == 0 ? Vector(0,0,1) : get_direction();
    position = position - dir * 10;
}

void Camera::set(Camera *camera){
    position = camera->position;
    aimPosition = camera->aimPosition;
    up = camera->up;
}


OrthoCamera::OrthoCamera(Vector position, Vector lookAt, Vector up)
: Camera(position, lookAt, up){}

Vector OrthoCamera::project(Vector v){
    auto tr = Matrix::lookAt(position, aimPosition, up) * v;
    return tr;
}

PerspecCamera::PerspecCamera(Vector position, Vector lookAt, Vector up, double d)
: Camera( position, lookAt, up ){
    this->d = d;
}

Vector PerspecCamera::project(Vector v){
    Vector transformed = Matrix::lookAt(position, aimPosition, up) * v;
    transformed = Matrix::perspectiveProjection(10, 30000, {-100,-100}, {100,100}) * transformed;
    transformed = transformed / (transformed.w);
    // if(transformed.z >= 0) transformed.z = 0.1;
    // transformed.x = transformed.x * d / ( transformed.z );
    // transformed.y = transformed.y * d / ( transformed.z );
    // transformed.z = 0;

    return transformed;
}