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

bool Sphere::hit(Ray &r) const{
    if(r.dir.dot(center - r.sup) < 0){
        return false; //hits behind support (viewpoint)
    }

    if(this->distRay(r) < radius){  //not = cause it'll go straigth anyway
        return true;
    }
    return false; 
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



Floor::Floor(Vec3D const center, Vec3D const color, num const tileSize):
    Object(center, color),
    tileSize (tileSize){
}

bool Floor::hit(Ray &r) const{
    num t;
    int u; 
    int v; // side/plane ("floor" can be on any axes)
    if(center[0] != 0){
        t = (center[0] - r.sup[0])/r.dir[0];
        u = 1;
        v = 2;  
    }
    else if(center[1] != 0){
        t = (center[1] - r.sup[1])/r.dir[1];
        u = 0;
        v = 2;
    } 
    else{
        t = (center[2] - r.sup[2])/r.dir[2];
        u = 0;
        v = 1;
    }

    if(t < 0){  //hits behind support (viewpoint)
        return false;
    }

    Vec3D p = r.at(t);

    // shifts over the grid on the negative axes to align
    if(p[u] < 0){
        p.setValue(u, p[u]-tileSize);
    }
    if(p[v] < 0){
        p.setValue(v, p[v]-tileSize);
    }

    Vec3D q = p % (tileSize*2);

    q.abs();

    if((q[u] < tileSize && q[v] < tileSize) || (q[u] >= tileSize && q[v] >= tileSize)){
        return true;
    }
    return false;
}
}