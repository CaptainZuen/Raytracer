#pragma once

#include "main.hpp"
#include "objects.hpp"

#define VPO st::vector <Object*>

namespace rayTracer{

class Object;   //include eachother

class Ray {
    
    protected:
        VPO objects;
        const int bounceLimit = 500;
        
    public:
        Vec3D sup; 
        Vec3D dir;
        num tMax = inf;
        num tMin = 0.0001;

        Ray(num xSup, num ySup, num zSup, num xDir, num yDir, num zDir);
        Ray(Vec3D &sup, Vec3D &dir);

        Ray(num xStart, num yStart, num screenDistance, VPO &objects);

        Vec3D at(num const &t) const;

        //checks objects list if it hits any, returns color
        Vec3D scan(int bounce);    

        void show(st::string label);
        
};
}