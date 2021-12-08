#include <list>
#include <chrono>

#include <future>

#include "main.hpp"
#include "objects/objects.hpp"
#include "rayScanner.hpp"
#include "io.hpp"


typedef st::chrono::high_resolution_clock Clock;


int main () {
    IO io = IO();
    srand(time(NULL));

    static const num d = 2;              //Distance to screen
    static const num w = 2.5;              //Width of screen
    static const num h = 2.5;              //Heigth of screen

    
    //Size of the rendered image
    
    static const int pW = 1000;           //Pixels wide
    static const int pH = 1000;           //Pixels high
    static const int rpP = 20;           //Rays per pixel

    const bool multi = false;

    //only for ascii prints
    static const num aspect = 1;         //Aspect ratio of width to height (i.e. cmd chars are 8x16, so 2)
    static const bool numbers = true;    //adds row and col numbers
    static const bool cross = false;     //adds cross in the middle


    // rt::Vec3D one = rt::Vec3D(1,0,0);
    // rt::Vec3D two = rt::Vec3D(0,1,0);
    // rt::Vec3D three = rt::Vec3D(0,0,1);

    // st::cout << one.angle(two)/pi*180 << '\n';
    // rt::Vec3D result = one.rotZ(one.angle(two));
    // result.show("Rotate");
    // st::cout << result.angle(one)/pi*180 << '\n';
    // st::cout << result.angle(two)/pi*180 << '\n';

    // rt::Sphere s = rt::Sphere(rt::Vec3D(1, -1, 0).unit()*10, rt::Vec3D(1, 0, 0), 10);
    

    // rt::Floor f = rt::Floor(rt::Vec3D(0, 0, 1), rt::Vec3D(0, 0, 0), 4);

    // rt::Ray r = rt::Ray(-1, 0, 0, 1, 0, 0);
    // r.show("r");
    // st::cout << s.hit(r) << " t\n";
    // rt::Vec3D hitPoint =  rt::Vec3D(0, 0, 0);
    // rt::Vec3D normal = s.normalOut(hitPoint);
    // normal.show("normal out");

    // rt::Vec3D result = s.reflectMirrored(r.dir, hitPoint);
    // result.show("Reflected");
    // st::cout << result.angle(r.dir)/pi*180 << '\n';
    // st::cout << result.angle(normal)/pi*180 << '\n';
    

    rt::RayScanner rs = rt::RayScanner();


    const int  mirror = 1;
    const int diffuse = 2;
    rt::Floor f = rt::Floor(rt::Vec3D(0, -3, 0), rt::Vec3D(0.6, 0, 1), 4, diffuse);
    rs.addObject(&f);

    st::list<rt::Sphere> Spheres;
    Spheres.push_back(rt::Sphere(rt::Vec3D(-4, -2, 16), rt::Vec3D(1, 0, 1), 1, diffuse));
    Spheres.push_back(rt::Sphere(rt::Vec3D(-6, -1 , 22), rt::Vec3D(0, 1, 0), 2, diffuse));
    Spheres.push_back(rt::Sphere(rt::Vec3D(4, -1.5 , 9), rt::Vec3D(1, 0.6, 0), 1.5, diffuse));

    Spheres.push_back(rt::Sphere(rt::Vec3D(2, -2.5, 13.5), rt::Vec3D(1, 1, 0), 0.6, mirror));
    Spheres.push_back(rt::Sphere(rt::Vec3D(9, 3, 40), rt::Vec3D(0.95, 0.95, 0.95), 6, mirror));
    Spheres.push_back(rt::Sphere(rt::Vec3D(0, 11, 24), rt::Vec3D(0.95, 0.95, 0.95), 10, mirror));
    Spheres.push_back(rt::Sphere(rt::Vec3D(70, 50, -50), rt::Vec3D(0, 1, 1), 50, mirror));

    Spheres.push_back(rt::Sphere(rt::Vec3D(0, -300, 15), rt::Vec3D(0.9, 0.9, 0.9), 297, diffuse));
    Spheres.push_back(rt::Sphere(rt::Vec3D(0, 0, 15), rt::Vec3D(0.5, 0.8, 0.8), 3, diffuse));

    Spheres.push_back(rt::Sphere(rt::Vec3D(15, 0, -18), rt::Vec3D(1, 0, 0.5), 15, diffuse));

    rs.addObjectList<rt::Sphere>(Spheres);

    // rt::Vec3D average = rt::Vec3D();
    // rt::Vec3D max = rt::Vec3D();
    // rt::Vec3D min = rt::Vec3D();
    // int count = 10000;
    // for(int i = 0; i < count; i++){
    //     rt::Vec3D temp = average.random();
    //     for(int j = 0; j < 3; j++){
    //         if(temp[j] > max[j]){
    //             max.setValue(j, temp[j]);
    //         }
    //         if(temp[j] < min[j]){
    //             min.setValue(j, temp[j]);
    //         }
    //     }
    //     average = average + temp;
    // }
    // (average/count).show("average");
    // max.show("max");
    // min.show("min");


    st::chrono::duration<double, st::milli> time;
    st::chrono::_V2::system_clock::time_point start;
    st::chrono::_V2::system_clock::time_point end;
    int count = 1;


    start = Clock::now();
    for(int i = 0; i < count; i++){
        
        st::string filename = "Scene_" + st::to_string(i+1);
        if(multi){
            io.ppm(filename, rs.scan(d, w, h, pW, pH, rpP));
        } else{
            io.ppm(filename, rs.scanSingle(d, w, h, pW, pH, rpP));
        }       

    }
    end = Clock::now();
    time = end-start;

    st::cout << "Average over " << count << ": " << (time/count).count() << "ms\n";

    st::string stats = st::to_string(pW) + '\t' + st::to_string(pH) + '\t' + st::to_string(rpP);
    stats += '\t' + st::to_string(count) + '\t' + st::to_string(static_cast<int>((time/count).count())) + '\t' + st::to_string(multi);
    io.file("scenes/Stats", stats);

    return 0;
}



