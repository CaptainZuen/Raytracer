#pragma once

#include "main.hpp"
#include "vec3D.hpp"
#include "ray.hpp"


namespace rayTracer{


class Object{
    protected:
        Vec3D center;
        Vec3D color;
        int reflection;

    public:
        Object(const num x, const num y, const num z, const num r, const num g, const num b, const int reflection);
        Object(const Vec3D center, const Vec3D color, const int reflection);

        Vec3D getColor();
        int getReflection();

        virtual Vec3D normalOut(const Ray &ray) const = 0;


        virtual num hit(const Ray &r) const = 0;      

};

class Sphere: public Object{
    protected:
        num radius;

    public:

        Sphere(const num x, const num y, const num z, const num r, const num g, const num b, const num radius, const int reflection);
        Sphere(const Vec3D center, const Vec3D color, const num radius, const int reflection);

        Vec3D normalOut(const Ray &ray) const;

        num distRay(const Ray &r) const;    //distance to the ray
        num hit(const Ray &r) const;
        Vec3D hitPoint(const Ray &r) const;

};

class Floor: public Object{
    protected:
        num tileSize;
        int plane;
        int otherPlaneOne;
        int otherPlaneTwo;
        Vec3D normal;

    public:

        Floor(const Vec3D center, const Vec3D color, const num tileSize, const int reflection);

        Vec3D normalOut(const Ray &ray) const;
        num hit(const Ray &r) const;


};
}