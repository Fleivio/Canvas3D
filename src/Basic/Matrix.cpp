#include "Matrix.h"

Matrix::Matrix(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matrix[i][j] = 0;
        }
    }
}

#include <iostream>
using namespace std;

void Matrix::print(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << "[" << matrix[i][j] << "]";
        }
        puts("");
    }
}

Matrix::Matrix(double matrix[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->matrix[i][j] = matrix[i][j];
        }
    }
}

Matrix Matrix::identity(){
    Matrix m = Matrix();
    for(int i = 0; i < 4; i++){
        m.matrix[i][i] = 1;
    }
    return m;
}

Matrix Matrix::translate(Vector v){
    Matrix m = Matrix::identity();
    m.matrix[0][3] = v.x;
    m.matrix[1][3] = v.y;
    m.matrix[2][3] = v.z;
    return m;
}

Matrix Matrix::scale(Vector v){
    Matrix m = Matrix::identity();
    m.matrix[0][0] = v.x;
    m.matrix[1][1] = v.y;
    m.matrix[2][2] = v.z;
    return m;
}

Matrix Matrix::scale(double delta){
    return Matrix::scale({delta, delta, delta});
}

Matrix Matrix::rotationX(double ang){
    double m[4][4] = {
        {1, 0       , 0        ,0},
        {0, cos(ang), -sin(ang),0},
        {0, sin(ang), cos(ang) , 0},
        {0, 0       , 0        ,1}
    };

    return Matrix(m);
}

Matrix Matrix::rotationY(double ang){
    double m[4][4] = {
        {cos(ang) , 0, sin(ang), 0},
        {0        , 1, 0       , 0},
        {-sin(ang), 0, cos(ang), 0},
        {0,0,0,1}
    };

    return Matrix(m);
}

Matrix Matrix::rotationZ(double ang){
    double m[4][4] = {
        {cos(ang), -sin(ang), 0, 0},
        {sin(ang), cos(ang),  0, 0},
        {0,0,1,0},
        {0,0,0,1}
    };

    return Matrix(m);
}


Matrix Matrix::rotation(Vector v){
    double x = v.x, y = v.y, z = v.z;

    return Matrix::rotationX(x) *
           Matrix::rotationY(y) *
           Matrix::rotationZ(z);
}


Matrix Matrix::orthoProjectionZ(){
    Matrix m = Matrix::identity();
    m.matrix[2][2] = 0;
    return m;
}

Matrix Matrix::orthoProjectionY(){
    Matrix m = Matrix::identity();
    m.matrix[1][1] = 0;
    return m;
}

Matrix Matrix::orthoProjectionX(){
    Matrix m = Matrix::identity();
    m.matrix[0][0] = 0;
    return m;
}

Matrix Matrix::changeBasis(Vector e1, Vector e2, Vector e3){
    double m[4][4] = {
        {e1.x, e1.y, e1.z, 0},
        {e2.x, e2.y, e2.z, 0},
        {e3.x, e3.y, e3.z, 0},
        {0, 0, 0, 1}
    };

    return Matrix(m);
}

Matrix Matrix::lookAt(Vector eye, Vector center, Vector top){
    // vetores da base da camera
    Vector normal = (eye - center).normalize();
    Vector right = top.cross(normal).normalize();
    Vector up = normal.cross(right).normalize();
    
    // translacao para o centro da camera
    Matrix minusT = Matrix::translate(eye * (-1));

    Matrix cam_base = Matrix::changeBasis(right, up, normal);

    return cam_base * minusT;
}

Matrix Matrix::perspectiveProjection(double far, double near, Vector bottomLeft, Vector topRight){
    double n = near;
    double f = far;
    double l = bottomLeft.x;
    double r = topRight.x;
    double b = bottomLeft.y;
    double t = topRight.y;
    
    Matrix m = Matrix::identity();
    m.matrix[0][0] = (2 * n) / (r - l);
    m.matrix[1][1] = (2 * n) / (t - b);
    m.matrix[2][2] = - (far + near) / (far - near);
    m.matrix[3][3] = 0;

    m.matrix[0][2] = (r + l) / (r - l);
    m.matrix[1][2] = (t + b) / (t - b);
    m.matrix[3][2] = -1;

    m.matrix[2][3] = - (2 * f * n) / (f - n);
    return m;
}

Matrix Matrix::operator*(Matrix m){
    Matrix aux = Matrix();
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            aux.matrix[i][j] = 0;
            for(int k = 0; k < 4; k++){
                aux.matrix[i][j] += this->matrix[i][k] * m.matrix[k][j];
            }
        }
    }
    return aux;
}

Vector Matrix::operator*(Vector v){
    Vector aux = v.copy().applyMatrix(matrix);
    return aux;
}



MatrixStack::MatrixStack(){
    this->reset();
}

void MatrixStack::stack_up(Matrix m){
    this->stacked = m * this->stacked;
}

void MatrixStack::reset(){
    this->stacked = Matrix::identity();
}

Vector MatrixStack::apply(Vector v){
    return this->stacked * v;
}

Matrix MatrixStack::apply(Matrix m){
    return this->stacked * m;
}
