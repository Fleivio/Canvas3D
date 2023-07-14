#ifndef ENGINE_G
#define ENGINE_G

#include "2D/Engine.h"
#include "3D/Engine3D.h"
#include "../gl_canvas3d.h"

class EngineGroup{
    private:
        static Engine e1;
        static Engine e2;

        static Engine3D engine3d1;
        static Engine3D engine3d2;

        static double angle;

        static void update(){
            engine3d1.update();
            engine3d2.update();
        }

        static void update_angle(){
            engine3d1.set_angle(-angle);
            engine3d2.set_angle(angle);
        }
    public:
        static void init(){
            engine3d1 = Engine3D(&e1, {0,0,10}, -angle);
            engine3d2 = Engine3D(&e2, {0,0,100}, angle);
        }

        static void render(){
            update();

            engine3d1.render();
            engine3d2.render();

            CV::translate({50,50});
            e1.draw();
            CV::translate({(double)CV3D::screenWidth - 50,50});
            e2.draw();
        }

        static void inc_angle(){
            angle += 0.2;
            update_angle();
        }

        static void dec_angle(){
            angle -= 0.2;
            update_angle();
        }
};


#endif