#ifndef _CANVAS3D_
#define _CANVAS3D_

/*API para a API do Pozzer, 
Possui uma camera e uma matriz de transformação acumulada, 
sempre que algo é renderizado, aplica-se as transformações e projeta-se na camera
a perspectiva da camaera pode ser alterada
*/

#include "Basic/Vector.h"
#include "Basic/Matrix.h"
#include "3D/Camera.h"
#include "Basic/Color.h"

//afeta apenas poligonos
typedef enum {
    FILL, WIREFRAME
} Mode;

//afeta apenas a camera
typedef enum {
    PERSPECTIVE, ORTHOGRAPHIC
} CameraMode;

class CV3D {
    private:
        static double info_distance;
        static double axis_size;
        
        static MatrixStack transformations;
        static Vector transform(Vector v);
        static Mode mode;
        static CameraMode camera_mode;
        static PerspecCamera pCamera;
        static OrthoCamera oCamera;
    public:
        static int screenWidth, screenHeight;
        static Camera *camera;
        
        static void stack_up_transformations(double transformation[4][4]);
        static void stack_up_transformations(Matrix m);

        static void reset_transformations();
        static void set_camera(Camera *camera);
        static void set_mode(Mode m);
        static void set_cam_mode(CameraMode m);

        static void draw_coordinate_system();
        static void draw_info();
        static void draw_coord_nums();

        static void translate(Vector v);
        static void scale(Vector v);
        static void scale(double factor);
        static void rotate(Vector v);

        static void color3d(float r, float g, float b);
        static void color3d(float r, float g, float b, float a);

        static void text3d(Vector v, int t);
        static void text3d(Vector v, double t);
        static void text3d(Vector v, float t);
        static void text3d(Vector v, const char *t);

        static void smallText3d(Vector v, int t);
        static void smallText3d(Vector v, double t);
        static void smallText3d(Vector v, float t);
        static void smallText3d(Vector v, const char *t);

        static void point3d(Vector v);
        static void line3d(Vector v1, Vector v2);
        static void triangle3d(Vector v1, Vector v2, Vector v3);
        static void quad3d(Vector v1, Vector v2, Vector v3, Vector v4);
        static void polygon3d(Vector *vertices, int n_vertices);
};

#endif