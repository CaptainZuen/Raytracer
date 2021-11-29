#include "vec3D.hpp"

namespace st = std;


namespace rayTracer{

Vec3D::Vec3D(num x, num y, num z){
    c[0] = x;
    c[1] = y;
    c[2] = z;
}

Vec3D::Vec3D(num s){
    c[0] = s;
    c[1] = s;
    c[2] = s;
}

Vec3D::Vec3D(Vec3D const &v){
    c[0] = v[0];
    c[1] = v[1];
    c[2] = v[2];
}

Vec3D::Vec3D(){
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
}



num Vec3D::operator [] (int i) const{
    return c[i];
}

void Vec3D::setValue(int index, num value){
    c[index] = value;
}



void Vec3D::show(st::string label) const{ 
    st::cout << label << ":\tx=" << c[0] << "\ty=" << c[1] << "\tz=" << c[2] << '\n';
}

void Vec3D::show(st::string label, num scalar) const{ 
    st::cout << label << " : " << scalar << '\n';
}

void Vec3D::show() const{ 
    st::cout << '\n';
}



  
Vec3D operator - (Vec3D const &v){
    return Vec3D(-v[0], -v[1], -v[2]);
}

Vec3D operator + (Vec3D const &v1, Vec3D const &v2){
    return Vec3D(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}
    
Vec3D operator - (Vec3D const &v1, Vec3D const &v2){
    return Vec3D(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}
    
Vec3D operator * (Vec3D const &v1, Vec3D const &v2){
    return Vec3D(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}
    
Vec3D operator / (Vec3D const &v1, Vec3D const &v2){
    return Vec3D(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

Vec3D operator % (Vec3D const &v1, Vec3D const &v2){
    return Vec3D(fmod(v1[0], v2[0]), fmod(v1[1], v2[1]), fmod(v1[2], v2[2]));
}
    
bool operator < (Vec3D const &v1, Vec3D const &v2){
    return v1[0] < v2[0] && v1[1] < v2[1] && v1[2] < v2[2];
}

bool operator > (Vec3D const &v1, Vec3D const &v2){
    return v1[0] > v2[0] && v1[1] > v2[1] && v1[2] > v2[2];
}



num Vec3D::norm() const{ 
    return sqrt( c[0]*c[0] + c[1]*c[1] + c[2]*c[2] );
}

Vec3D Vec3D::unit() const{ 
    //catches a divide by 0
    if(c[0] == 0 && c[1] == 0 && c[2] == 0){
        return *this;
    }
    else{
        return *this / this->norm();
    }
}

num Vec3D::dot(Vec3D const &other) const{ 
    return c[0]*other[0] + c[1]*other[1] + c[2]*other[2];
} 
                                        
Vec3D Vec3D::cross(Vec3D const &other) const{ 
    return Vec3D( c[1]*other[2] - c[2]*other[1], c[2]*other[0] - c[0]*other[2], c[0]*other[1] - c[1]*other[0]);
} 


Vec3D Vec3D::abs() const{
    return Vec3D(st::abs(c[0]), st::abs(c[1]), st::abs(c[2]));
}

num Vec3D::angle(Vec3D const &v)const {
    return st::acos(this->dot(v));
}

Vec3D Vec3D::rotX(num const angle) const{
    num cos = st::cos(angle);
    num sin = st::sin(angle);

    num one = c[0];
    num two = c[1]*cos - c[2]*sin;
    num thr = c[1]*sin + c[2]*cos;

    return Vec3D(one, two, thr);
}

Vec3D Vec3D::rotY(num const angle) const{
    num cos = st::cos(angle);
    num sin = st::sin(angle);

    num one = c[0]*cos + c[2]*sin;
    num two = c[1];
    num thr = -c[0]*sin + c[2]*cos;

    return Vec3D(one, two, thr);
}

Vec3D Vec3D::rotZ(num const angle) const{
    num cos = st::cos(angle);
    num sin = st::sin(angle);

    num one = c[0]*cos - c[1]*sin;
    num two = c[0]*sin + c[1]*cos;
    num thr = c[2]; 

    return Vec3D(c[0]*cos - c[1]*sin, c[0]*sin + c[1]*cos, c[2]);
}

Vec3D Vec3D::random() const{
    num r =  RAND_MAX/2;
    num x = rand() - r;
    num y = rand() - r;
    num z = rand() - r;

    return Vec3D(x, y, z).unit();
}
}