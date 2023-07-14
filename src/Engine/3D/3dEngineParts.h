#ifndef _3D_ENGINE_PARTS
#define _3D_ENGINE_PARTS

/*implementa classes individuais para as partes do motor, simplifica na hora de renderizar tudo na classe Engine3D
Contrapeso
Pistao
Camisa
Biela
*/

#include "../../gl_canvas3d.h"
#include "../../Basic/Vector.h"
#include "../2D/Engine.h"
#include "../../3D/MeshGenerator.h"
#include "../../3D/Mesh.h"
#include "../../gl_canvas2d.h"

#include <vector>
using namespace std;

class Contrapeso3d {
    static double contrapeso_h;
    static double contrapeso_r;
    static double contrapeso_dist;

    private:
        Mesh contraGrande;
        Mesh contraPequeno;
        Mesh liga1;
        Mesh liga2;

    public:
        Contrapeso3d(){}

        Contrapeso3d(Engine* eng, Vector globalPos, bool isUp);

        void update();

        void render();

        static double get_height();

        static double get_radius();

        static double get_dist();
};

class Pistao3d {
    private:
        Vector piston_last_position;
        Mesh piston;
        Engine *eng;

    public:
        Pistao3d(){};
        Pistao3d(Engine *eng);
        void update();
        void render();
};

class Camisa3d {
    private:
        static double camisa_r;
        Mesh camisa;
    public:
        Camisa3d(){}
        Camisa3d(Engine *eng);
        void render();
};

class Biela3d {
    private:
        static double biela_r;
        Mesh conexao;
        Mesh pino;
        Mesh pinoPonta;
        Engine *eng;
    public:
        Biela3d(){}

        Biela3d(Engine* eng);

        void update();

        void render();

        static double get_radius();
};

#endif
