/*Implementa uma classe para vetor de duas dimensões, útil para pontos*/
#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <math.h>
#include <stdio.h>

class Vector
{
public:
    double x, y, z, w;

    void print()
    {
        printf("x: %f, y: %f, z: %f\n", x, y, z);
    }

    /*cria Vector(0,0)*/
    Vector();
    /*cria um vetor com coordenadas x,y*/
    Vector(double x, double y);
    Vector(double x, double y, double z);
    Vector(double x, double y, double z, double w);

    ~Vector() = default;

    Vector clockwisePerpendicular2D();

    double mod();

    /*seta uma nova coordenada*/
    void set(double x, double y);
    void set(double x, double y, double z);
    void set(double x, double y, double z, double w);

    /*seta novas coordenadas iguais a vec*/
    void set(Vector &vec);

    /*normaliza o vetor*/
    Vector normalize();

    /*verifica a igualdade entre dois vetores*/
    bool equals(Vector &vec);

    /*verifica a distancia entre dois pontos*/

    double dot(Vector v);
    Vector cross(Vector v);

    /*verifica a distancia entre dois pontos*/
    double distance(double x, double y);
    double distance(double x, double y, double z);
    double distance(double x, double y, double z, double w);
    double distance(Vector v);

    Vector applyMatrix(double matrix[4][4]);
    Vector applyMatrix(double matrix[3][3]);

    Vector rotacionaX(double angulo);
    Vector rotacionaY(double angulo);
    Vector rotacionaZ(double angulo);
    
    Vector translate(double x, double y, double z);

    Vector projectXY();
    Vector projectXZ();
    Vector projectYZ();

    Vector ortoProjXY(double d);

    /*retorna uma cópia do vetor original*/
    Vector copy();

    //Operandos
    Vector operator - (const Vector &v) {
        Vector aux(x - v.x, y - v.y, z - v.z);
        return (aux);
    }

    Vector operator+(const Vector &v) {
        Vector aux(x + v.x, y + v.y, z + v.z);
        return (aux);
    }

    void operator+=(const Vector &v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
    }

    Vector operator/(const Vector &v) {
        Vector aux(x / v.x, y / v.y, z / v.z);
        return (aux);
    }

    bool operator==(const Vector &v) {
        return x == v.x && y == v.y && z == v.z;
    }

    bool operator!=(const Vector &v) {
        return x != v.x || y != v.y || z != v.z;
    }

    Vector operator/(double scale) {
        return {x / scale, y / scale, z / scale};
    }

    Vector operator*(double scale) {
        return {x * scale, y * scale, z * scale};
    }

    Vector operator*(const Vector &v) {
        return {x * v.x, y * v.y, z * v.z};
    }

    void operator*=(const Vector &v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
    }
};

#endif
