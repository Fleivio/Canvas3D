#ifndef _3D_ENGINE
#define _3D_ENGINE

/*Classe da engine 3d, acessa o modelo 2d do motor e atualiza suas partes,
possui várias partes 3d separadas*/

#include "../../gl_canvas3d.h"
#include "../../Basic/Vector.h"
#include "../2D/Engine.h"
#include "3dEngineParts.h"

#include <iostream>
using namespace std;


class Engine3D{
    private:
        double angle;
        Vector position;

        Camisa3d camisa;
        Pistao3d piston;
        Biela3d biela;
        Contrapeso3d contrapeso1;
        Contrapeso3d contrapeso2;

        void init_contrapeso();

        void contrapeso_update();

    public:
        Engine *eng;
        static bool render_pistao;
        static bool render_camisa;
        static bool render_biela;
        static bool render_contrapeso;
        static bool pause;

        Engine3D();
        Engine3D(Engine *eng, Vector position);
        Engine3D(Engine *eng, Vector position, double ang);

        void update();

        void set_angle(double ang);

        void render();
};


#endif
