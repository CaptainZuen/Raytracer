#include "objects.hpp"


namespace rayTracer{

Object::Object(num const x, num const y, num const z, num const r, num const g, num const b):
    center (x, y, z),
    color (r, g, b){
}
Object::Object(Vec3D const center, Vec3D const color):
    center (center),
    color (color){   
}

Vec3D Object::getColor(){
    return color;
}

Vec3D Object::normalOut(Vec3D const &hitPoint) const{
    return (hitPoint-center).unit();
}

//-----------------------------------------------------------------------------------------
//Sphere::


Sphere::Sphere(num const x, num const y, num const z, num const r, num const g, num const b, num const radius):
    Object(x, y, z, r, g, b),
    radius (radius){
}
Sphere::Sphere(Vec3D const center, Vec3D const color, num const radius):
    Object(center, color),
    radius (radius){
}

 

num Sphere::distRay(Ray const &r) const{
    // num t = r.dir.dot(center - r.sup);     //time on ray (dist from support/origin in direction lengths)
    // Vec3D p = r.at(t);             //Closest point to center
    // num distance = (center-p).norm();
    
    //substitution:
    return (center-(r.sup + r.dir * r.dir.dot(center - r.sup))).norm();
}

num Sphere::hit(Ray const &r) const{
    num t = r.dir.dot(center - r.sup);

    if(t + radius < r.tMin){
        return -1; //hits behind support (viewpoint)
    }

    num dis = this->distRay(r);

    if(dis < radius){  //not = cause it'll go straigth anyway
        num x = sqrt(radius * radius - dis * dis);
        if(t - x < r.tMin){
            return t + x;
        }
        return t - x;
    }
    return -1; 
}

Vec3D Sphere::hitPoint(Ray const &r) const{
    num dis = this->distRay(r);
    // num t = r.dir.dot(center - r.sup);
     
    // num t1 = t - sqrt(radius * radius - dis * dis); //sqrt always +, first hitpoint lowest t, so only t-sqrt()
    // num t2 = t + sqrt(radius * radius - dis * dis);

    // Vec3D hitPoint = r.at(t1);

    //substitution:
    return r.at((r.dir.dot(center - r.sup)) - sqrt(radius * radius - dis * dis));
}


void Sphere::bounce(Ray&r) const{

}




//------------------------------------------------------------------------------------------
//Floor:



Floor::Floor(Vec3D const center, Vec3D const color, num const tileSize):
    Object(center, color),
    tileSize (tileSize){
    if(center[0] != 0){
        plane = 0;
        otherPlaneOne = 1;
        otherPlaneTwo = 2;  
    }
    else if(center[1] != 0){
        plane = 1;
        otherPlaneOne = 0;
        otherPlaneTwo = 2;
    } 
    else{
        plane = 2;
        otherPlaneOne = 0;
        otherPlaneTwo = 1;
    }
}

num Floor::hit(Ray const &r) const{

    num t = (center[plane] - r.sup[plane])/r.dir[plane];

    if(t < r.tMin | t > r.tMax){  //hits behind support or after other object
        return -1;
    }

    Vec3D p = r.at(t);

    // shifts over the grid on the negative axes to align
    if(p[otherPlaneOne] < 0){
        p.setValue(otherPlaneOne, p[otherPlaneOne]-tileSize);
    }
    if(p[otherPlaneTwo] < 0){
        p.setValue(otherPlaneTwo, p[otherPlaneTwo]-tileSize);
    }

    Vec3D q = p % (tileSize*2);

    q.abs();

    if((q[otherPlaneOne] < tileSize && q[otherPlaneTwo] < tileSize) | (q[otherPlaneOne] >= tileSize && q[otherPlaneTwo] >= tileSize)){
        return t;
    }
    return -1;
}

void Floor::bounce(Ray &r) const{

}

}