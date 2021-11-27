#pragma once

#include "main.hpp"

namespace rayTracer{

class Ray;  //include eachother

class Object{
    protected:
        Vec3D center;
        Vec3D color;
        int reflection;

    public:
        Object(num const x, num const y, num const z, num const r, num const g, num const b, int const reflection);
        Object(Vec3D const center, Vec3D const color, int const reflection);

        Vec3D getColor();

        virtual Vec3D normalOut(Vec3D const &hitPoint) const = 0;

        Vec3D bounce(Vec3D const &dir, Vec3D const &hitPoint) const;
        Vec3D reflectMirrored(Vec3D const &dir, Vec3D const &hitPoint) const;
        Vec3D reflectDiffuse(Vec3D const &dir, Vec3D const &hitPoint) const;

        virtual num hit(Ray const &r) const = 0;      

};

class Sphere: public Object{
    protected:
        num radius;

    public:

        Sphere(num const x, num const y, num const z, num const r, num const g, num const b, num const radius, int const reflection);
        Sphere(Vec3D const center, Vec3D const color, num const radius, int const reflection);

        Vec3D normalOut(Vec3D const &hitPoint) const;

        num distRay(Ray const &r) const;    //distance to the ray
        num hit(Ray const &r) const;
        Vec3D hitPoint(Ray const &r) const;

};

class Floor: public Object{
    protected:
        num tileSize;
        int plane;
        int otherPlaneOne;
        int otherPlaneTwo;

    public:

        Floor(Vec3D const center, Vec3D const color, num const tileSize, int const reflection);

        Vec3D normalOut(Vec3D const &hitPoint) const;
        num hit(Ray const &r) const;


};
}