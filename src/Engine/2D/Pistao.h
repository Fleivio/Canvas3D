#ifndef PISTAO
#define PISTAO

#include "../../Basic/Vector.h"

/*pistao, recebe uma posicao do virabrequim, é basicamente apenas um retangulo que varia*/

class Pistao {
    private:
        double var_range;
        double raio;

        void set_is_up(bool isUp);

    public:
        Vector get_bottom_right_position();
        Vector get_top_left_position();
        double altura_cilindro;
        double altura_cabeca;
        Vector center_position;
        Vector bottom_position_cabeca;

        Pistao(Vector position, bool isUp, double raio, double altura_cabeca, double altura_cilindro);

        void set_bottom_y(double y);
        void draw();
};


#endif
