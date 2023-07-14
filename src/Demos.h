#ifndef DEMOS
#define DEMOS

/*demos 3d para testes de render*/

#include "gl_canvas2d.h"
#include "3D/Mesh.h"
#include "3D/MeshGenerator.h"

class Demos {
    static Mesh sphere;
    static Mesh sphere2;
    static Mesh cilinder1;
    static Mesh torus;
    static Mesh mobius;
    static Mesh cube;
    static Mesh hexPrism;
    static Mesh hollowCilinder;
    static Mesh elipsoid;
    static Mesh plane;
    static Mesh parabH;
    static Mesh parabE;
    static Mesh cone;

    public:
        static void init_demos(){
            sphere = MeshGenerator::genSphere(Vector(-100,0,-50), 20);
            cilinder1 = MeshGenerator::genCilinder(Vector(-100,0,-150), 20, 20);
            torus = MeshGenerator::genTorus(Vector(-100,0,-200), 20, 10);

            mobius = MeshGenerator::genMobius({});
            mobius.mapTransform(Matrix::scale(15));
            mobius.mapTransform(Matrix::translate({-100, 0, -250}));

            cube = MeshGenerator::genPrism(Vector(-100,0,-300), 20, 20, 4);
            hexPrism = MeshGenerator::genPrism(Vector(-100,0,-350), 20, 20, 6);
            hollowCilinder = MeshGenerator::genHollowCilinder(Vector(-100,0,-400), 20, 20, 10);
            elipsoid = MeshGenerator::genElipsoid(Vector(-100,0,-450), 20, 10, 5);
            plane = MeshGenerator::genPlane({0,0,0}, {0,0,100}, {0,100,100}, {0,100,0});

            parabH = MeshGenerator::genParabHip( {}, 50, 50, 1, 1);
            parabH.mapTransform(Matrix::rotationX({PI/2}));
            parabH.mapTransform(Matrix::translate({-100, 0, 50}));

            parabE = MeshGenerator::genParabElip({}, 20, 20, 50);
            parabE.mapTransform(Matrix::rotationX({PI/2}));
            parabE.mapTransform(Matrix::translate({-100, 0, 100}));

            cone = MeshGenerator::genCone({}, 20, 20, 100);
            cone.mapTransform(Matrix::rotationX({PI/2}));
            cone.mapTransform(Matrix::translate({-100, 0, 150}));
        }

        static void render_demos(){
            CV::color(1,1,1);

            cube.render();
            sphere.render();
            cilinder1.render();
            torus.render();
            mobius.render();
            cube.render();
            hexPrism.render();
            hollowCilinder.render();
            elipsoid.render();
            plane.render();
            parabH.render();
            parabE.render();

            // cone.render();
        }
};

#endif