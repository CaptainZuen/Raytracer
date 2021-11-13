#pragma once
#include <iostream>

#include "vec3D.hpp"
#include "ray.hpp"

namespace st = std;

namespace rayTracer{

class Ray;  //include eachother

class Object{
    protected:
        Vec3D center;

    public:
        Object(num const x, num const y, num const z);
        Object(Vec3D const center);

        virtual bool hit(Ray &r) const = 0;

};

class Sphere: public Object{
    protected:
        num radius;

    public:

        Sphere(num const x, num const y, num const z, num const radius);
        Sphere(Vec3D const center, num const radius);

        num distRay(Ray const &r) const;    //distance to the ray
        bool hit(Ray &r) const;
        Vec3D hitPoint(Ray const &r) const;

};

class Floor: public Object{
    protected:
        num tileSize;

    public:

        Floor(Vec3D const center, num const tileSize);

        bool hit(Ray &r) const;


};
}