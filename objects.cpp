#include "objects.hpp"


namespace rayTracer{

Object::Object(num const x, num const y, num const z):
    center (x, y, z){
}
Object::Object(Vec3D const center):
    center (center){   
}



//-----------------------------------------------------------------------------------------
//Sphere::


Sphere::Sphere(num const x, num const y, num const z, num const radius):
    Object(x, y, z),
    radius (radius){
}
Sphere::Sphere(Vec3D const center, num const radius):
    Object(center),
    radius (radius){
}

 

num Sphere::distRay(Ray const &r) const{
    // num t = r.dir.dot(center - r.sup);     //time on ray (dist from support/origin in direction lengths)
    // Vec3D p = r.sup + r.dir * t;             //Closest point to center
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

    // Vec3D hitPoint = r.sup + r.dir * t1;

    //substitution:
    return r.sup + r.dir * ((r.dir.dot(center - r.sup)) - sqrt(radius * radius - dis * dis));
}





//------------------------------------------------------------------------------------------
//Floor:



Floor::Floor(Vec3D const center, num const tileSize):
    Object(center),
    tileSize (tileSize){
}

bool Floor::hit(Ray &r) const{
    num t = 0;
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

    Vec3D p = r.sup + r.dir * t;

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