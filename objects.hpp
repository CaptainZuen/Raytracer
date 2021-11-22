#pragma once

#include "main.hpp"

namespace rayTracer{

class Ray;  //include eachother

class Object{
    protected:
        Vec3D center;
        Vec3D color;

    public:
        Object(num const x, num const y, num const z, num const r, num const g, num const b);
        Object(Vec3D const center, Vec3D const color);

        Vec3D getColor();

        virtual bool hit(Ray &r) const = 0;
        virtual void bounce(Ray &r) const = 0;

        

};

class Sphere: public Object{
    protected:
        num radius;

    public:

        Sphere(num const x, num const y, num const z, num const r, num const g, num const b, num const radius);
        Sphere(Vec3D const center, Vec3D const color, num const radius);

        num distRay(Ray const &r) const;    //distance to the ray
        bool hit(Ray &r) const;
        Vec3D hitPoint(Ray const &r) const;

        void bounce(Ray&r) const;

};

class Floor: public Object{
    protected:
        num tileSize;

    public:

        Floor(Vec3D const center, Vec3D const color, num const tileSize);

        bool hit(Ray &r) const;


};
}