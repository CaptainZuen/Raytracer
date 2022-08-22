#pragma once
#include <iterator>

#include "main.hpp"
#include "vec3D.hpp"
#include "ray.hpp"
#include "objects/objects.hpp"

#define VPO st::vector <Object*>
#define rndr st::vector<st::vector<rt::Vec3D>>
extern thread_local MyRNG* rng;

namespace rayTracer{

struct Screen{
    const num distance = 0;
    const num width = 0;
    const num height = 0;

    const int pixelsWide = 0;
    const int pixelsHigh = 0;

    const int raysPPixel = 0;

    const num halfpixelsWide = 0.5*(width/pixelsWide);
    const num halfpixelsHigh = 0.5*(height/pixelsHigh);
    const num offsetX = width/2 + halfpixelsWide;
    const num offsetY = height/2 + halfpixelsHigh;

    Screen(const num distance, const num width, const num height, const int pixelsWide, const int pixelsHigh, const int raysPPixel):
    distance (distance),
    width (width),
    height (height),
    pixelsWide (pixelsWide),
    pixelsHigh (pixelsHigh),
    raysPPixel (raysPPixel){
    }

};

class RayScanner{
    protected:
        Screen scr;
        VPO objects;
        const int depthLimit = 15;

    public:
        RayScanner(Screen scr);
        void addObject(Object* object);


        //rendering
        rndr scanSingle();
        rndr scan();


        //template to add a list of objects
        template <typename T> void addObjectList(st::list<T> &objectList){
            typename st::list<T> :: iterator i;
            for(i = objectList.begin(); i != objectList.end(); ++i){
                objects.push_back(&*i);
            }
        }
};
}