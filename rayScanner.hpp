#pragma once
#include <iostream>
#include <iterator>
#include <fstream>

#include "vec3D.hpp"
#include "ray.hpp"

#define scr st::vector<st::vector<int>> 

using namespace std;

namespace rayTracer{

class RayScanner{
    protected:
        st::string chars = " .:-=+*#%@";

        num screenDistance;
        num screenWidth;
        num screenHeight;

        int pixelWidth;
        int pixelHeight;

        VPO objects;

    public:

        RayScanner(num screenDistance, num screenWidth, num screenHeight, int pixelWidth, int pixelHeight);

        scr scan(); //renders the screen
        void print(scr screen, num aspect, bool numbers, bool cross); //add row and col numbers and/or cross in the middle
        void print(st::string fileName, num aspect, scr screen, bool numbers, bool cross);

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