#ifndef MESH
#define MESH

#include "../Basic/Vector.h"
#include "../Basic/Matrix.h"
#include "../gl_canvas3d.h"
#include <vector>
using namespace std;

#define vecVec vector< vector<Vector> >

class Mesh {
    private:
        vecVec vertices;

    public:
        Mesh(){
            this->vertices = vecVec();
        }

        Mesh(vecVec vertices) {
            this->vertices = vertices;
        }

        vecVec getVertices() {
            return this->vertices;
        }

        void setVertices(vecVec vertices) {
            this->vertices = vertices;
        }

        void mapTransform(Matrix m){
            for(auto &vec : vertices){
                for(auto &v : vec){
                    v = m * v;
                }
            }
        }

        void mapTransform(double mat[4][4]){
            for(auto &vec : vertices){
                for(auto &v : vec){
                    v = v.applyMatrix(mat);
                }
            }
        }

        void render(){
            for (size_t i = 0; i < vertices.size(); i++ ){
                for (size_t j = 0; j < vertices[i].size(); j++ ){
                    if (i < vertices.size() - 1 && j < vertices[i].size() - 1){
                        CV3D::triangle3d(vertices[i][j], vertices[i + 1][j], vertices[i][j + 1]);
                        CV3D::triangle3d(vertices[i + 1][j], vertices[i + 1][j + 1], vertices[i][j + 1]);
                    }
                }
            }
        }

        Mesh copy(){
            vecVec newVertices = vecVec();
            for(auto &vec : vertices){
                vector<Vector> newVec = vector<Vector>();
                for(auto &v : vec){
                    newVec.push_back(v);
                }
                newVertices.push_back(newVec);
            }
            return Mesh(newVertices);
        }
};

#endif
