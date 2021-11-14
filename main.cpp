#include <iostream>
#include <vector>
#include <string> 
#include <stack>
#include <cmath>
#include <list>

#include "vec3D.hpp"
#include "ray.hpp"
#include "objects.hpp"
#include "rayScanner.hpp"
#include "io.hpp"

namespace st = std;
namespace rt = rayTracer;


int main () {
    num d = 3;              //Distance to screen
    num w = 4;              //Width of screen
    num h = 4;              //Heigth of screen


    //Size of the rendered image
    
    int pW = 200;           //Pixels wide
    int pH = 100;           //Pixels high
    
    num aspect = 1;         //Aspect ratio of width to height (i.e. cmd chars are 8x16, so 2)
    bool numbers = true;    //adds row and col numbers
    bool cross = false;     //adds cross in the middle

    rt::RayScanner rs = rt::RayScanner(d, w, h, pW, pH);


    rt::Floor f = rt::Floor(rt::Vec3D(0, -4, 0), 4);
    rs.addObject(&f);


    st::list<rt::Sphere> Spheres;
    Spheres.push_back(rt::Sphere(-15, 5, 80, 5));
    Spheres.push_back(rt::Sphere(5, -1, 150, 12));
    Spheres.push_back(rt::Sphere(6, 2, 20, 2));
    Spheres.push_back(rt::Sphere(-50, 100, 100, 90));

    rs.addObjectList<rt::Sphere>(Spheres);

    scr screenOne = rs.scanGrey();

    IO io = IO();
    io.print(screenOne, aspect, numbers, cross);
    io.print("Scene_1", screenOne, aspect, numbers, cross);


    return 0;
}



