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




Vec3D& Ray::scan(VPO &objects, Vec3D &color, int bounce){
    if(bounce <= 0){
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        return color;
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
        color *= current->getColor(); 
        if(color < 0.003906) return color; 
        scan(objects, color, --bounce);      
        return color;
    }

    color[0] *= (1 - ((dir[1] + 1)/2) * 0.5);
    color[1] *= (1 - ((dir[1] + 1)/2) * 0.3);
    return color;

}
}

