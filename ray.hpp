#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "vec3D.hpp"
#include "objects.hpp"

#define VPO st::vector <Object*>

namespace rayTracer{

class Object;   //include eachother

class Ray {
    
    protected:
        VPO objects;
        
    public:
        Vec3D sup; 
        Vec3D dir;

        Ray(num xSup, num ySup, num zSup, num xDir, num yDir, num zDir);
        Ray(Vec3D &sup, Vec3D &dir);

        Ray(num xStart, num yStart, num screenDistance, VPO &objects);

        bool scan();    //checks objects list if it hits any

        void show(st::string label);
        
};
}