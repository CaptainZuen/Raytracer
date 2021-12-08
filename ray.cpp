#include "ray.hpp"


namespace rayTracer{

Ray::Ray (num xSup, num ySup, num zSup, num xDir, num yDir, num zDir){
    sup = Vec3D(xSup, ySup, zSup);
    dir = Vec3D(xDir, yDir, zDir).unit();
}

Ray::Ray (const Vec3D &sup, const Vec3D &dir)
    :sup (sup), dir (dir){
}

Ray::Ray(const num xStart, const num yStart, const num screenDistance){
    sup = Vec3D(0, 0, -screenDistance);
    dir = Vec3D(xStart, yStart, screenDistance).unit();
}

Vec3D Ray::at(const num &t) const{
    return sup + t*dir;
}

Vec3D Ray::scan(VPO &objects, int bounce){
    if(bounce <= 0){
        return Vec3D();
    }

    tMax = inf;
    Object* current = NULL;
    for(auto &object: objects){
        num t = object->hit(*this);
        if(t > tMin && t < tMax){
            tMax = t;
            current = object;
        }
    }
    if(current != NULL){
        sup = at(tMax);
        dir = current->bounce(dir, sup);        
        return current->getColor() * scan(objects, --bounce);
    }

    return Vec3D(1) - ((dir[1] + 1)/2) * Vec3D(0.5, 0.3, 0);

}

void Ray::show(st::string label) const{
    st::cout << label << '\n';
    sup.show("Ray support");
    dir.show("Ray direction");
}

}

