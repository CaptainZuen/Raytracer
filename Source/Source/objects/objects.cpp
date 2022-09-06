#include "../../objects.hpp"


namespace rayTracer{

Object::Object(const num x, const num y, const num z, const num r, const num g, const num b, const int reflection):
    center (x, y, z),
    color (r, g, b),
    reflection (reflection){
}
Object::Object(const Vec3D center, const Vec3D color, const int reflection):
    center (center),
    color (color),
    reflection (reflection){   
}

Vec3D Object::getColor(){
    return color;
}

int Object::getReflection(){
    return reflection;
}




//-----------------------------------------------------------------------------------------
//Sphere::


Sphere::Sphere(const num x, const num y, const num z, const num r, const num g, const num b, const num radius, const int reflection):
    Object(x, y, z, r, g, b, reflection),
    radius (radius){
}
Sphere::Sphere(const Vec3D center, const Vec3D color, const num radius, const int reflection):
    Object(center, color, reflection),
    radius (radius){
}


Vec3D Sphere::normalOut(const Ray &ray) const{
    Vec3D normal = (ray.sup-center).unit();

    if(normal.dot(ray.dir) > 0.){
        normal = -normal;
    }
    return normal;
}
 
num Sphere::distRay(const Ray &r) const{
    // num t = r.dir.dot(center - r.sup);     //time on ray (dist from support/origin in direction lengths)
    // Vec3D p = r.at(t);             //Closest point to center
    // num distance = (center-p).norm();
    
    //substitution:
    return (center-(r.sup + r.dir * r.dir.dot(center - r.sup))).norm();
}

num Sphere::hit(const Ray &r) const{
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

Vec3D Sphere::hitPoint(const Ray &r) const{
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



Floor::Floor(const Vec3D center, const Vec3D color, const num tileSize, const int reflection):
    Object(center, color, reflection),
    tileSize (tileSize){
    if(center[0] != 0){
        plane = 0;
        otherPlaneOne = 1;
        otherPlaneTwo = 2; 
        normal = Vec3D(1,0,0);
    }
    else if(center[1] != 0){
        plane = 1;
        otherPlaneOne = 0;
        otherPlaneTwo = 2;
        normal = Vec3D(0,1,0);
    } 
    else{
        plane = 2;
        otherPlaneOne = 0;
        otherPlaneTwo = 1;
        normal = Vec3D(0,0,1);
    }
}

Vec3D Floor::normalOut(const Ray &ray) const{
    if(normal.dot(ray.dir) > 0.){
        return -normal;
    }
    return normal;
}

num Floor::hit(const Ray &r) const{

    num t = (center[plane] - r.sup[plane])/r.dir[plane];

    if(t < r.tMin | t > r.tMax){  //hits behind support or after other object
        return -1;
    }

    Vec3D p = r.at(t);

    // shifts over the grid on the negative axes to align
    if(p[otherPlaneOne] < 0){
        p[otherPlaneOne] -= tileSize;
    }
    if(p[otherPlaneTwo] < 0){
        p[otherPlaneTwo] -= tileSize;
    }

    Vec3D q = p % (tileSize*2);

    q.abs();

    if((q[otherPlaneOne] < tileSize && q[otherPlaneTwo] < tileSize) | (q[otherPlaneOne] >= tileSize && q[otherPlaneTwo] >= tileSize)){
        return t;
    }
    return -1;
}
}