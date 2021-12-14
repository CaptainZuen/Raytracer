#pragma once

#include "main.hpp"
#include "objects/objects.hpp"

#define VPO st::vector <Object*>

namespace rayTracer{

class Object;   //include eachother

class Ray {
    
    protected:
        
    public:
        Vec3D sup; 
        Vec3D dir;
        num tMax = inf;
        static constexpr num tMin = 0.0001;

        Ray(num xSup, num ySup, num zSup, num xDir, num yDir, num zDir);
        Ray(const Vec3D &sup, const Vec3D &dir);

        Ray(const num xStart, const num yStart, const num screenDistance);

        Vec3D at(const num &t) const;

        //checks objects list if it hits any, returns color
        Vec3D& scan(VPO &objects, Vec3D &color, int bounce);

        void show(st::string label) const;
        
};
}