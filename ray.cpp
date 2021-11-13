#include "ray.hpp"


namespace rayTracer{

Ray::Ray (num xSup, num ySup, num zSup, num xDir, num yDir, num zDir){
    sup = Vec3D(xSup, ySup, zSup);
    dir = Vec3D(xDir, yDir, zDir).unit();
}

Ray::Ray (Vec3D &sup, Vec3D &dir)
    :sup (sup), dir (dir){
}

Ray::Ray(num xStart, num yStart, num screenDistance, VPO &objects):
    objects (objects){
    sup = Vec3D(0, 0, -screenDistance);
    dir = Vec3D(xStart, yStart, screenDistance).unit();
}


bool Ray::scan(){
    for(auto object: objects){
        if(object->hit(*this)){
            return true;
        }
    }
    return false;
}

void Ray::show(st::string label){
    st::cout << label << '\n';
    sup.show("Ray support");
    dir.show("Ray direction");
}

}

