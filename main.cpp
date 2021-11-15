#include <iostream>
#include <vector>
#include <string> 
#include <stack>
#include <cmath>
#include <list>
#include <chrono>

#include "vec3D.hpp"
#include "ray.hpp"
#include "objects.hpp"
#include "rayScanner.hpp"
#include "io.hpp"

namespace st = std;
namespace rt = rayTracer;

typedef st::chrono::high_resolution_clock Clock;


int main () {
    IO io = IO();

    num d = 3;              //Distance to screen
    num w = 3;              //Width of screen
    num h = 1.5;              //Heigth of screen


    //Size of the rendered image
    
    int pW = 1500;           //Pixels wide
    int pH = 750;           //Pixels high
    
    //only for ascii prints
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




    rt::RayScanner rs_2 = rt::RayScanner(d, w, h, pW, pH);

    rt::Floor f_2 = rt::Floor(rt::Vec3D(0, -20, 0), 4);
    rs_2.addObject(&f_2);

    st::list<rt::Sphere> Spheres_2;
    Spheres_2.push_back(rt::Sphere(15, -5, 80, 7));
    Spheres_2.push_back(rt::Sphere(5, 10, 150, 12));
    Spheres_2.push_back(rt::Sphere(-6, 5, 20, 4));
    Spheres_2.push_back(rt::Sphere(50, 125, 100, 70));

    rs_2.addObjectList<rt::Sphere>(Spheres_2);





    st::chrono::duration<double, st::milli> time;
    st::chrono::_V2::system_clock::time_point start;
    st::chrono::_V2::system_clock::time_point end;
    int count = 5;

    for(int i = 0; i < count; i++){
        start = Clock::now();
        scrRGB screen_1 = rs.scanRGB();
        io.ppm("Scene_1", screen_1);

        scrRGB screen_2 = rs_2.scanRGB();
        io.ppm("Scene_2", screen_2);

        end = Clock::now();
        time+= end-start;
    }

    st::cout << "Average over " << count << ": " << (time/count).count() << "ms\n";


    return 0;
}



