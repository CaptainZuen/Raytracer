#pragma once

#include "main.hpp"
#include "vec3D.hpp"


namespace rayTracer{

class Ray {
    
    protected:
        
    public:
        Vec3D sup; 
        Vec3D dir;
        num tMax = inf;
        static constexpr num tMin = 0.01;

        Ray(num xSup, num ySup, num zSup, num xDir, num yDir, num zDir);
        Ray(const Vec3D &sup, const Vec3D &dir);

        Ray(const num xStart, const num yStart, const num screenDistance);

        Vec3D at(const num &t) const;


        void show(st::string label) const;
        
};
}