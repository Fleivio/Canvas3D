#ifndef _CAMERA_
#define _CAMERA_

/*Classes para camera, possuem os três vetores que definem uma camera: eye, up e direção
A OrthoCamera projeta ortogonalmente
A PerspecCamera projeta em perspectiva
*/

#include "../Basic/Vector.h"
#include "../Basic/Matrix.h"

class Camera {
    public:
        Vector position;
        Vector aimPosition;
        Vector up;

        Camera(Vector position, Vector aimPosition, Vector up);
        Camera();

        Vector get_direction();
        void rotate_camera(Vector v);

        void map_transformation(Matrix m);

        void zoom_in();
        void zoom_out();
        void set(Camera *camera);

        virtual Vector project(Vector v) = 0 ;
};

class OrthoCamera : public Camera{
    public:
        OrthoCamera(Vector position, Vector aim, Vector up);

        Vector project(Vector v) override;
};

class PerspecCamera : public Camera{
    public:
        double d;
        PerspecCamera(Vector position, Vector aim, Vector up, double d);

        Vector project(Vector v) override;
};


#endif
