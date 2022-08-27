#include "ray.hpp"


namespace rayTracer{

Ray::Ray (num xSup, num ySup, num zSup, num xDir, num yDir, num zDir){
    sup = Vec3D(xSup, ySup, zSup);
    dir = Vec3D(xDir, yDir, zDir).unit();
}

Ray::Ray (const Vec3D &sup, const Vec3D &dir)
    :sup (sup), dir (dir){
    this->dir.unit();
}

Ray::Ray(const num xStart, const num yStart, const num screenDistance){
    sup = Vec3D(0, 0, -screenDistance);
    dir = Vec3D(xStart, yStart, screenDistance).unit();
}



void Ray::show(st::string label) const{
    st::cout << label << '\n';
    sup.show("Ray support");
    dir.show("Ray direction");
}



Vec3D Ray::at(const num &t) const{
    return sup + t*dir;
}


void Ray::bounce(const Vec3D& normal, int reflection){

    switch(reflection){
        case 1:
            mirrorReflect(normal);
            return;
        case 2:
            diffuseReflect(normal);
            return;
    }
}

void Ray::mirrorReflect(const Vec3D& normal){
    dir = dir - 2*dir.dot(normal)*normal;
}

void Ray::diffuseReflect(const Vec3D& normal){
    dir.random();
    if(normal.dot(dir) < 0.){
        dir = -dir;
    }
}
}

