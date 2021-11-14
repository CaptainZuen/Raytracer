#pragma once
#include <iostream>
#include <iterator>

#include "vec3D.hpp"
#include "ray.hpp"

#define scr st::vector<st::vector<int>> 
#define scrRGB st::vector<st::vector<Vec3D>>


namespace rayTracer{

class RayScanner{
    protected:
        num screenDistance;
        num screenWidth;
        num screenHeight;

        int pixelWidth;
        int pixelHeight;

        VPO objects;

    public:

        RayScanner(num screenDistance, num screenWidth, num screenHeight, int pixelWidth, int pixelHeight);

        scr scanGrey(); //renders the screen
        scrRGB scanRGB();
        
        

        void addObject(Object* object);

        //template to add a list of objects
        template <typename T> void addObjectList(st::list<T> &objectList){
            typename st::list<T> :: iterator i;
            for(i = objectList.begin(); i != objectList.end(); ++i){
                objects.push_back(&*i);
            }
        }
};
}