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

Vec3D::Vec3D(num* s){
    c[0] = s[0];
    c[1] = s[1];
    c[2] = s[2];
}

Vec3D::Vec3D(){
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
}



Vec3D::Vec3D(const Vec3D &v){
    c[0] = v[0];
    c[1] = v[1];
    c[2] = v[2];
}

// Vec3D::Vec3D(Vec3D &&v):
//     c (v.c){
//     v.c = nullptr;
//     // st::cout << "move" << st::endl;
// }

// Vec3D::~Vec3D(){
//     // st::cout << "destruct ";
//     // if(c == nullptr) st::cout << "nullptr" << st::endl;
//     // else st::cout << "filled" << st::endl;
//     delete[] c;
// }

//--------------------------------------------------------------------------


//Operators:
num Vec3D::operator [] (int i) const{
    return c[i];
}

num& Vec3D::operator [] (int i){
    return c[i];
}
//--------------------------------------------------------

Vec3D& Vec3D::operator = (const Vec3D &v){
    c[0] = v[0];
    c[1] = v[1];
    c[2] = v[2];
    return *this;
}

// Vec3D& Vec3D::operator = (Vec3D &&v){
//     delete[] c;
//     c = v.c;
//     v.c = nullptr;
//     return *this;
//     // c = st::move(v.c);

//     // c[0] = v[0];
//     // c[1] = v[1];
//     // c[2] = v[2];
//     // return *this;
// }

Vec3D& Vec3D::operator *= (const Vec3D &v){
    c[0] *= v[0];
    c[1] *= v[1];
    c[2] *= v[2];
    return *this;
}

Vec3D& Vec3D::operator += (const Vec3D &v){
    c[0] += v[0];
    c[1] += v[1];
    c[2] += v[2];
    return *this;
}

Vec3D& Vec3D::operator /= (const Vec3D &v){
    c[0] /= v[0];
    c[1] /= v[1];
    c[2] /= v[2];
    return *this;
}
//--------------------------------------------------------


Vec3D Vec3D::operator - (){
    return Vec3D(-c[0], -c[1], -c[2]);
}

Vec3D Vec3D::operator - (const Vec3D &v){
    return Vec3D(c[0] - v[0], c[1] - v[1], c[2] - v[2]);
}

Vec3D Vec3D::operator + (const Vec3D &v){
    return Vec3D(c[0] + v[0], c[1] + v[1], c[2] + v[2]);
}
    
Vec3D Vec3D::operator * (const Vec3D &v){
    return Vec3D(c[0] * v[0], c[1] * v[1], c[2] * v[2]);
}
    
Vec3D Vec3D::operator / (const Vec3D &v){
    return Vec3D(c[0] / v[0], c[1] / v[1], c[2] / v[2]);
}

Vec3D Vec3D::operator % (const Vec3D &v){
    return Vec3D(fmod(c[0], v[0]), fmod(c[1], v[1]), fmod(c[2], v[2]));
}
//---------------------------------------------------------




Vec3D operator - (const Vec3D &v){
    return Vec3D(-v[0], -v[1], -v[2]);
}

Vec3D operator + (const Vec3D &v1, const Vec3D &v2){
    return Vec3D(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}
    
Vec3D operator - (const Vec3D &v1, const Vec3D &v2){
    return Vec3D(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}
    
Vec3D operator * (const Vec3D &v1, const Vec3D &v2){
    return Vec3D(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}
    
Vec3D operator / (const Vec3D &v1, const Vec3D &v2){
    return Vec3D(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
}

Vec3D operator % (const Vec3D &v1, const Vec3D &v2){
    return Vec3D(fmod(v1[0], v2[0]), fmod(v1[1], v2[1]), fmod(v1[2], v2[2]));
}

bool operator < (const Vec3D &v1, const Vec3D &v2){
    return v1[0] < v2[0] && v1[1] < v2[1] && v1[2] < v2[2];
}

bool operator > (const Vec3D &v1, const Vec3D &v2){
    return v1[0] > v2[0] && v1[1] > v2[1] && v1[2] > v2[2];
}

//--------------------------------------------------------------------------------




Vec3D& Vec3D::setValue(const num value){
    c[0] = value;
    c[1] = value;
    c[2] = value;
    return *this;
}




void Vec3D::show(st::string label) const{ 
    st::cout << label << ":\tx=" << c[0] << "\ty=" << c[1] << "\tz=" << c[2] << '\n';
}

void Vec3D::show(st::string label, num scalar) const{ 
    st::cout << label << " : " << scalar << '\n';
}

void Vec3D::show() const{ 
    st::cout << "x=" << c[0] << "\ty=" << c[1] << "\tz=" << c[2] << '\n';
}








num Vec3D::norm() const{ 
    return sqrt( c[0]*c[0] + c[1]*c[1] + c[2]*c[2] );
}

Vec3D& Vec3D::unit(){ 
    //catches a divide by 0
    if(c[0] == 0 && c[1] == 0 && c[2] == 0){
        return *this;
    }
    else{
        return *this /= this->norm();
    }
}



num Vec3D::dot(const Vec3D &other) const{ 
    return c[0]*other[0] + c[1]*other[1] + c[2]*other[2];
} 
                                        
Vec3D& Vec3D::cross(const Vec3D &other){
    c[0] = c[1]*other[2] - c[2]*other[1];
    c[1] = c[2]*other[0] - c[0]*other[2];
    c[2] = c[0]*other[1] - c[1]*other[0];
    return *this;
} 


Vec3D& Vec3D::abs(){
    c[0] = st::abs(c[0]);
    c[1] = st::abs(c[1]); 
    c[2] = st::abs(c[2]);
    return *this;
}

num Vec3D::angle(const Vec3D &v)const {
    return st::acos(this->dot(v));
}

Vec3D& Vec3D::rotX(const num angle){
    num cos = st::cos(angle);
    num sin = st::sin(angle);

    c[1] = c[1]*cos - c[2]*sin;
    c[2] = c[1]*sin + c[2]*cos;

    return *this;
}

Vec3D& Vec3D::rotY(const num angle){
    num cos = st::cos(angle);
    num sin = st::sin(angle);

    c[0] = c[0]*cos + c[2]*sin;
    c[2] = -c[0]*sin + c[2]*cos;

    return *this;
}

Vec3D& Vec3D::rotZ(const num angle){
    num cos = st::cos(angle);
    num sin = st::sin(angle);

    c[0] = c[0]*cos - c[1]*sin;
    c[1] = c[0]*sin + c[1]*cos; 

    return *this;
}

Vec3D& Vec3D::random(){
    num r =  RAND_MAX/2;
    c[0] = rand() - r;
    c[1] = rand() - r;
    c[2] = rand() - r;

    return this->unit();
}
}