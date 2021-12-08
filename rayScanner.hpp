#pragma once
#include <iterator>
#include <list>

#include "main.hpp"

namespace rt = rayTracer;
#define scr st::vector<st::vector<rt::Vec3D>>

namespace rayTracer{

class RayScanner{
    protected:
        VPO objects;
        const int bounceLimit = 15;

    public:

        RayScanner();

        //rendering
        scr scanSingle(const num screenDistance, const num screenWidth, const num screenHeight, const int pixelWidth, const int pixelHeight, const int raysPPixel);
        scr scan(const num screenDistance, const num screenWidth, const num screenHeight, const int pixelWidth, const int pixelHeight, const int raysPPixel);

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