#include "Vector.h"

Vector::Vector()
{
    set(0,0,0);
}

Vector::Vector(double x, double y)
{
    set(x, y);
}

Vector::Vector(double x, double y, double z)
{
    set(x, y, z);
}

Vector::Vector(double x, double y, double z, double w)
{
    set(x, y, z, w);
}

void Vector::set(double x, double y)
{
    set(x, y, 0);
}

void Vector::set(double x, double y, double z){
    set(x, y, z, 1);
}

void Vector::set(double x, double y, double z, double w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Vector::set(Vector &vec)
{
    set(vec.x, vec.y, vec.z, vec.w);
}

Vector Vector::normalize()
{
    double norm = (double)sqrt(x * x + y * y + z * z + w * w);

    if (norm == 0.0)
    {
        set(1, 0, 0, 0);
        return *this;
    }

    x /= norm;
    y /= norm;
    z /= norm;
    w /= norm;

    return *this;
}

double Vector::dot(Vector v){
    return x*v.x + y*v.y + z*v.z + w*v.w;
}

Vector Vector::cross(Vector v){
    Vector aux = Vector();
    aux.x = y*v.z - z*v.y;
    aux.y = z*v.x - x*v.z;
    aux.z = x*v.y - y*v.x;
    aux.w = 0;
    return aux;
}


double Vector::mod(){
    return sqrt(x * x + y * y + z*z + w*w);
}

double Vector::distance(double x, double y)
{
    return (double)sqrt(pow(this->x - x, 2) + pow(this->y - y, 2));
}

double Vector::distance(double x, double y, double z)
{
    return (double)sqrt(pow(this->x - x, 2) + pow(this->y - y, 2) + pow(this->z - z, 2));
}

double Vector::distance(double x, double y, double z, double w)
{
    return (double)sqrt(pow(this->x - x, 2) + pow(this->y - y, 2) + pow(this->z - z, 2) + pow(this->w - w, 2));
}

double Vector::distance(Vector v)
{
    return distance(v.x, v.y, v.z, v.w);
}

Vector Vector::copy()
{
    return Vector(x, y, z, w);
}

bool Vector::equals(Vector &vec)
{
    return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
}

Vector Vector::clockwisePerpendicular2D(){
    return Vector(y, -x);
}

Vector Vector::applyMatrix(double matrix[3][3]){
    double x = this->x;
    double y = this->y;
    double z = this->z;

    Vector aux = Vector();
    aux.x = x*matrix[0][0] + y*matrix[0][1] + z*matrix[0][2];
    aux.y = x*matrix[1][0] + y*matrix[1][1] + z*matrix[1][2];
    aux.z = x*matrix[2][0] + y*matrix[2][1] + z*matrix[2][2];
    return aux;
}

Vector Vector::applyMatrix(double matrix[4][4]){

    Vector aux = Vector();
    aux.x = x*matrix[0][0] + y*matrix[0][1] + z*matrix[0][2] + w*matrix[0][3];
    aux.y = x*matrix[1][0] + y*matrix[1][1] + z*matrix[1][2] + w*matrix[1][3];
    aux.z = x*matrix[2][0] + y*matrix[2][1] + z*matrix[2][2] + w*matrix[2][3];
    aux.w = x*matrix[3][0] + y*matrix[3][1] + z*matrix[3][2] + w*matrix[3][3];

    return aux;
}

Vector Vector::rotacionaX(double ang){
    Vector aux = Vector();
    aux.x = this->x;
    aux.y = this->y*cos(ang) - this->z*sin(ang);
    aux.z = this->y*sin(ang) + this->z*cos(ang);
    return aux;
}

Vector Vector::rotacionaY(double ang){
    Vector aux = Vector();
    aux.x = this->x*cos(ang) + this->z*sin(ang);
    aux.y = this->y;
    aux.z = -this->x*sin(ang) + this->z*cos(ang);
    return aux;
}

Vector Vector::rotacionaZ(double ang){
    Vector aux = Vector();
    aux.x = this->x*cos(ang) - this->y*sin(ang);
    aux.y = this->x*sin(ang) + this->y*cos(ang);
    aux.z = this->z;
    return aux;
}

Vector Vector::translate(double x, double y, double z){
    Vector aux = Vector();
    aux.x = this->x + x;
    aux.y = this->y + y;
    aux.z = this->z + z;
    return aux;
}

Vector Vector::projectXY(){
    Vector aux = Vector();
    aux.x = this->x;
    aux.y = this->y;
    return aux;
}

Vector Vector::projectXZ(){
    Vector aux = Vector();
    aux.x = this->x;
    aux.z = this->z;
    return aux;
}

Vector Vector::projectYZ(){
    Vector aux = Vector();
    aux.y = this->y;
    aux.z = this->z;
    return aux;
}

Vector Vector::ortoProjXY(double d){
    Vector aux = Vector();
    aux.x = (d*this->x) / this->z;
    aux.y = (d*this->y) / this->z;
    return aux;
}
