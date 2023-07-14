#ifndef MESH_GENERATOR
#define MESH_GENERATOR

#include "../Basic/Vector.h"
#include "Mesh.h"


class MeshGenerator {
    private:
        static double angleResolution;
        static double radiusResolution;
        static double angleStep;
        static double radiusStep;
    public:
        static Mesh genSphere(Vector center, double radius);
        static Mesh genCilinder(Vector bottomCenter, double height, double radius);
        static Mesh genCilinder(Vector bottomCenter, Vector topCenter, double radius);
        static Mesh genTorus(Vector center, double radius, double radius2);
        static Mesh genMobius(Vector center);
        static Mesh genPrism(Vector bottomCenter, double height, double radius, int sides);
        static Mesh genHollowCilinder(Vector bottomCenter, double height, double radius, double thickness);
        static Mesh genPlane(Vector v1, Vector v2, Vector v3, Vector v4);
        static Mesh genElipsoid(Vector center, double radiusX, double radiusY, double radiusZ);
        static Mesh genParabElip(Vector center, double rx, double ry, double h);
        static Mesh genParabHip(Vector center, double xLen, double yLen, double a, double b);
        static Mesh genCone(Vector center, double rx, double ry, double h);
};

#endif