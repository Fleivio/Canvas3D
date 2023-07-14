#ifndef VIRABREQUIM
#define VIRABREQUIM

/*classe do virabrequim, atualiza o angulo constantemente*/

#include "../../Basic/Vector.h"

class Virabrequim {
    private:
        static double ang_speed;
        static double center_rad;
    public:
        double radius;
        double angle;
        Vector center_position;

        Virabrequim(Vector position, double act_angle, double radius);

        void update();
        double get_angle();

        Vector get_position();
        Vector get_opposite_position();

        static double get_ang_speed();

        static void inc_speed();
        static void dec_speed();

        void draw();
};

#endif
