#pragma once

#include "main.hpp"
#include "objects/objects.hpp"

#define VPO st::vector <Object*>

namespace rayTracer{

class Object;   //include eachother

class Ray {
    
    protected:
        // VPO const objects;
        
    public:
        Vec3D sup; 
        Vec3D dir;
        num tMax = inf;
        static constexpr num tMin = 0.0001;

        Ray(num xSup, num ySup, num zSup, num xDir, num yDir, num zDir);
        Ray(Vec3D const &sup, Vec3D const &dir);

        // Ray(num const xStart, num const yStart, num const screenDistance, VPO const &objects);
        Ray(num const xStart, num const yStart, num const screenDistance);

        Vec3D at(num const &t) const;

        //checks objects list if it hits any, returns color
        Vec3D scan(VPO &objects, int bounce);    

        void show(st::string label) const;
        
};
}