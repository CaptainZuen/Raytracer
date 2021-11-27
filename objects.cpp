#include "objects.hpp"


namespace rayTracer{

Object::Object(num const x, num const y, num const z, num const r, num const g, num const b, int const reflection):
    center (x, y, z),
    color (r, g, b),
    reflection (reflection){
}
Object::Object(Vec3D const center, Vec3D const color, int const reflection):
    center (center),
    color (color),
    reflection (reflection){   
}

Vec3D Object::getColor(){
    return color;
}

Vec3D Object::bounce(Vec3D const &dir, Vec3D const &hitPoint) const{
    switch(reflection){
        case 1:
            return this->reflectMirrored(dir, hitPoint);
            break;
        case 2:
            return this->reflectDiffuse(dir, hitPoint);
            break;
    }
    return Vec3D();
}

Vec3D Object::reflectMirrored(Vec3D const &dir, Vec3D const &hitPoint) const{
    Vec3D normal = this->normalOut(hitPoint);
    if(normal.dot(dir) > 0.){
        normal = -normal;
    }
    return dir - 2*dir.dot(normal)*normal;
}

Vec3D Object::reflectDiffuse(Vec3D const &dir, Vec3D const &hitPoint) const{
    Vec3D normal = this->normalOut(hitPoint);
    if(normal.dot(dir) > 0.){
        normal = -normal;
    }
    Vec3D random = normal.random();
    if(normal.dot(random) < 0.){
        random = -random;
    }
    return random;
}


//-----------------------------------------------------------------------------------------
//Sphere::


Sphere::Sphere(num const x, num const y, num const z, num const r, num const g, num const b, num const radius, int const reflection):
    Object(x, y, z, r, g, b, reflection),
    radius (radius){
}
Sphere::Sphere(Vec3D const center, Vec3D const color, num const radius, int const reflection):
    Object(center, color, reflection),
    radius (radius){
}


Vec3D Sphere::normalOut(Vec3D const &hitPoint) const{
    return (hitPoint-center).unit();
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




//------------------------------------------------------------------------------------------
//Floor:



Floor::Floor(Vec3D const center, Vec3D const color, num const tileSize, int const reflection):
    Object(center, color, reflection),
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

Vec3D Floor::normalOut(Vec3D const &hitPoint) const{
    Vec3D temp = Vec3D();
    temp.setValue(plane, 1);
    return temp;
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
}