#ifndef ENGINE
#define ENGINE

/*modelo 2d do motor, une o virabrequim ao pistão e a comunicaçao entre as posições*/

#include "../../Basic/Vector.h"
#include "Virabrequim.h"
#include "Pistao.h"

class Engine {
    private:
        double calc_pistao_y();

        double raio;
    public:
        double biela;
        static double raio_pistao;
        static double cabeca_altura;
        Virabrequim *vib;
        Pistao *pis;

        Engine();
        Engine(Vector position, bool isUp, double raio, double biela);

        void draw();
        void update();
};

#endif
