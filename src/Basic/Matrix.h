#ifndef _MATRIX_
#define _MATRIX_

/*classe de matriz muito util para as transformações lineares, simplifica as tranformações do 3d e implementa
aplicações em vetores e multiplicação de matrizes*/

#include "Vector.h"

class Matrix {
    
    public:
        double matrix[4][4];

        Matrix();
        Matrix(double matrix[4][4]);

        void print();

        static Matrix identity();
        static Matrix translate(Vector v);

        static Matrix changeBasis(Vector e1, Vector e2, Vector e3);

        static Matrix scale(Vector v);
        static Matrix scale(double delta);

        static Matrix lookAt(Vector eye, Vector center, Vector top);
        static Matrix perspectiveProjection(double far, double near, Vector bottomLeft, Vector topRight);

        static Matrix rotationX(double ang);
        static Matrix rotationY(double ang);
        static Matrix rotationZ(double ang);
        static Matrix rotation(Vector v);

        static Matrix orthoProjectionZ();
        static Matrix orthoProjectionY();
        static Matrix orthoProjectionX();

        Matrix operator*(Matrix m);
        Vector operator*(Vector v);

};

class MatrixStack{
    private:
        Matrix stacked;
    public:
        MatrixStack();
        void stack_up(Matrix m);
        void reset();
        Vector apply(Vector v);
        Matrix apply(Matrix m);
};


#endif