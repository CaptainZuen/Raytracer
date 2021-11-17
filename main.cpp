#include <list>
#include <chrono>

#include "main.hpp"
#include "objects.hpp"
#include "rayScanner.hpp"
#include "io.hpp"


typedef st::chrono::high_resolution_clock Clock;


int main () {
    IO io = IO();

    num d = 3;              //Distance to screen
    num w = 2;              //Width of screen
    num h = 2;              //Heigth of screen


    //Size of the rendered image
    
    int pW = 800;           //Pixels wide
    int pH = 800;           //Pixels high
    
    //only for ascii prints
    num aspect = 1;         //Aspect ratio of width to height (i.e. cmd chars are 8x16, so 2)
    bool numbers = true;    //adds row and col numbers
    bool cross = false;     //adds cross in the middle





    rt::RayScanner rs = rt::RayScanner();

    rt::Floor f = rt::Floor(rt::Vec3D(0, -4, 0), rt::Vec3D(0, 0, 0), 4);
    rs.addObject(&f);

    st::list<rt::Sphere> Spheres;
    Spheres.push_back(rt::Sphere(rt::Vec3D(-15, -5, 80), rt::Vec3D(1, 0, 1), 5));
    Spheres.push_back(rt::Sphere(rt::Vec3D(5, -1, 150), rt::Vec3D(0, 1, 1), 12));
    Spheres.push_back(rt::Sphere(rt::Vec3D(6, 0, 20), rt::Vec3D(1, 1, 0), 2));
    Spheres.push_back(rt::Sphere(rt::Vec3D(-40, 100, 400), rt::Vec3D(1, 1, 1), 90));
    Spheres.push_back(rt::Sphere(rt::Vec3D(0, -4, 15), rt::Vec3D(1, 0, 0), 2));

    rs.addObjectList<rt::Sphere>(Spheres);






    st::chrono::duration<double, st::milli> time;
    st::chrono::_V2::system_clock::time_point start;
    st::chrono::_V2::system_clock::time_point end;
    int count = 1;

    for(int i = 0; i < count; i++){
        start = Clock::now();

        scrRGB screen_1 = rs.scanRGB(d, w, h, pW, pH);
        io.ppm("Scene_1", screen_1);

        end = Clock::now();
        time+= end-start;
    }

    st::cout << "Average over " << count << ": " << (time/count).count() << "ms\n";


    return 0;
}



