#include "MeshGenerator.h"
#include <algorithm>
using namespace std;
#define M_PI		3.14159265358979323846

double MeshGenerator::angleResolution = 10;
double MeshGenerator::radiusResolution = 5;
double MeshGenerator::angleStep = M_PI / angleResolution;

Mesh MeshGenerator::genSphere(Vector center, double radius){
    return genElipsoid(center, radius, radius, radius);
}

Mesh MeshGenerator::genCilinder(Vector bottomCenter, double height, double radius){
    auto vertices = vecVec();
    if(height == 0) height = 1;

    double radiusStep = height / radiusResolution;

    for(double phi = 0; phi <= height; phi += radiusStep) {
        vector<Vector> line = vector<Vector>();

        for(double theta = 0; theta <= 2*M_PI; theta += angleStep){
            double x = radius * cos(theta);
            double y = radius * sin(theta);
            double z = phi;

            Vector a = bottomCenter + Vector(x, y, z);
            line.push_back(a);
        }

        vertices.push_back(line);
    }
    return Mesh(vertices);
}

Mesh MeshGenerator::genCilinder(Vector bottomCenter, Vector topCenter, double radius){
    auto vertices = vecVec();

    Vector direction = topCenter - bottomCenter;

    for(double z = 0; z <= 1; z += 0.1) {
        vector<Vector> line = vector<Vector>();

        for(double theta = 0; theta <= 2*M_PI; theta += angleStep){
            double x = radius * cos(theta);
            double y = radius * sin(theta);

            Vector a = bottomCenter + (direction * z) + Vector(x, y, 0);
            line.push_back(a);
        }

        vertices.push_back(line);
    }
    return Mesh(vertices);
}

Mesh MeshGenerator::genTorus(Vector center, double R, double r){
    auto vertices = vecVec();

    double phi;
    for(phi = 0; phi <= 2 * M_PI; phi += angleStep) {
        vector<Vector> line = vector<Vector>();

        double theta;
        for(theta = 0; theta <= 2 * M_PI; theta += angleStep){
            double x = (R + r * cos(phi)) * cos(theta);
            double y = (R + r * cos(phi)) * sin(theta);
            double z = r * sin(phi);

            Vector a = center + Vector(x, y, z);
            line.push_back(a);
        }

        vertices.push_back(line);
    }

    return Mesh(vertices);
}

Mesh MeshGenerator::genMobius(Vector center){
    auto vertices = vecVec();

    double u;
    for(u = 0; u <= 2 * M_PI; u += angleStep) {
        vector<Vector> line = vector<Vector>();

        double v;
        for(v = -1; v <= 1; v += 0.05){
            double x = (1 + v/2 * cos(u/2)) * cos(u);
            double y = (1 + v/2 * cos(u/2)) * sin(u);
            double z = v/2 * sin(u/2);

            Vector a = center + Vector(x, y, z);
            line.push_back(a);
        }

        vertices.push_back(line);
    }

    auto mesh = Mesh(vertices);
    return mesh;
}

Mesh MeshGenerator::genPrism(Vector bottomCenter, double height, double radius, int sides){
    auto vertices = vecVec();

    double radiusStep = height / radiusResolution;
    double sideStep = 2 * M_PI / sides;

    for(double phi = 0; phi <= height; phi += radiusStep) {
        vector<Vector> line = vector<Vector>();

        for(double theta = 0; theta <= 2*M_PI; theta += sideStep){
            double x = radius * cos(theta);
            double y = radius * sin(theta);
            double z = phi;

            Vector a = bottomCenter + Vector(x, y, z);
            line.push_back(a);
        }

        vertices.push_back(line);
    }
    return Mesh(vertices);
}

Mesh MeshGenerator::genHollowCilinder(Vector bottomCenter, double height, double radius, double thickness){
    auto vertices = vecVec();
    double radiusStep = height / radiusResolution;

    double theta;
    for(theta = 0; theta <= 2 * M_PI; theta += angleStep ){
        vector<Vector> line = vector<Vector>();

        double h;
        for(h = 0; h <= height; h += radiusStep){
            double x = radius * cos(theta);
            double y = radius * sin(theta);
            double z = h;

            Vector a = bottomCenter + Vector(x, y, z);
            line.push_back(a);
        }
        h -= radiusStep;
        for(; h >= 0; h -= radiusStep){
            double x = (radius + thickness) * cos(theta);
            double y = (radius + thickness) * sin(theta);
            double z = h;

            Vector a = bottomCenter + Vector(x, y, z);
            line.push_back(a);
        }

        double x = radius * cos(theta);
        double y = radius * sin(theta);
        double z = h + radiusStep;
        Vector a = bottomCenter + Vector(x, y, z);
        line.push_back(a);

        vertices.push_back(line);
    }

    return Mesh(vertices);
}

Mesh MeshGenerator::genPlane(Vector v1, Vector v2, Vector v3, Vector v4){
    auto vertices = vecVec();

    Vector aStep = (v2 - v1);
    Vector bStep = (v4 - v1);

    for(double a = 0; a <= 1; a += 0.1){
        vector<Vector> line = vector<Vector>();

        for(double b = 0; b <= 1; b += 0.1){
            Vector v = (aStep * a) + (bStep * b);
            line.push_back(v + v1);
        }

        vertices.push_back(line);
    }

    return Mesh(vertices);
}

Mesh MeshGenerator::genElipsoid(Vector center, double rx, double ry, double rz){
    auto vertices = vecVec();

    double phi;
    for(phi = 0; phi <= 2 * M_PI; phi += angleStep) {
        vector<Vector> line = vector<Vector>();

        double theta;
        for(theta = 0; theta <= 2 * M_PI; theta += angleStep){
            double x = rx * cos(theta) * cos(phi);
            double y = ry * sin(theta) * cos(phi);
            double z = rz * sin(phi);

            Vector a = center + Vector(x, y, z);
            line.push_back(a);
        }

        vertices.push_back(line);
    }

    return Mesh(vertices);
}

Mesh MeshGenerator::genParabElip(Vector center, double rx, double ry, double h){
    auto vertices = vecVec();

    double phi;
    for(phi = 0; phi <= 2 * M_PI; phi += angleStep) {
        vector<Vector> line = vector<Vector>();

        double theta;
        for(theta = 0; theta <= 2 * M_PI; theta += angleStep){
            double x = rx * cos(theta) * cos(phi);
            double y = ry * sin(theta) * cos(phi);
            double z = h * sin(phi) * sin(phi);

            Vector a = center + Vector(x, y, z);
            line.push_back(a);
        }

        vertices.push_back(line);
    }

    return Mesh(vertices);
}

Mesh MeshGenerator::genParabHip(Vector center, double xLen, double yLen, double a, double b){
    auto vertices = vecVec();

    double xres = xLen / radiusResolution;
    double yres = yLen / radiusResolution;

    double x;
    for(x = -xLen/2; x <= xLen/2; x += xres/2) {
        vector<Vector> line = vector<Vector>();

        double y;
        for(y = -yLen/2; y <= yLen/2; y += yres/2){
            double z = ((x*x)/(a*a) - (y*y)/(b*b))/10;

            Vector v = center + Vector(x, y, z);
            line.push_back(v);
        }

        vertices.push_back(line);
    }

    return Mesh(vertices);
}

Mesh MeshGenerator::genCone(Vector center, double rx, double ry, double h){
    auto vertices = vecVec();

    double phi;
    for(phi = 0; phi <= 2 * M_PI; phi += angleStep) {
        vector<Vector> line = vector<Vector>();

        double theta;
        for(theta = 0; theta <= 2 * M_PI; theta += angleStep){
            double x = rx * cos(theta) * cos(phi);
            double y = ry * sin(theta) * cos(phi);
            double z = h * sin(phi);

            Vector a = center + Vector(x, y, z);
            line.push_back(a);
        }

        vertices.push_back(line);
    }

    return Mesh(vertices);
}
