#pragma once
#include <iterator>
#include <list>

#include "main.hpp"

namespace rt = rayTracer;
#define scr st::vector<st::vector<rt::Vec3D>>
#define scrFut st::vector<st::vector<st::shared_future<rt::Vec3D>>>

namespace rayTracer{

class RayScanner{
    protected:
        VPO objects;
        int const bounceLimit = 100;

    public:

        RayScanner();

        //rendering
        scr scan(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel);
        scrFut scanMulti(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel);
        scr scanTest(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel);
        scr scanTestRow(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel);

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