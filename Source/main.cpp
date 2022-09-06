#include "main.hpp"
#include "objects.hpp"
#include "rayScanner.hpp"
#include "io.hpp"

#include "vec3D.hpp"
#include "ray.hpp"




int main (int argc, char *argv[]) {
    IO io = IO();

    if(argc != 5) {
        st::cout << "Error: Include 4 arguments for width, height, root of subpixels and rays per pixel\n";
        return 1;
    }


    static const num d = 3;              //Distance to screen
    // static const num w = 2;              //Width of screen
    static const num h = 2;              //height of screen

    
    //Size of the rendered image
    static const int pW = st::atoi(argv[1]);             //Pixels wide
    static const int pH = st::atoi(argv[2]);             //Pixels high
    static const int sPR = st::atoi(argv[3]);             //Subpixel root, to form a square of subpixels
    static const int rpP = st::atoi(argv[4]);             //Random rays per (sub)pixel

    static const num w = static_cast<num>(pW)/pH * h;
    // static const num h = static_cast<num>(pH)/pW * w;
    const bool multi = true;


    //only for ascii prints
    static const num aspect = 1;         //Aspect ratio of width to height (i.e. cmd chars are 8x16, so 2)
    static const bool numbers = true;    //adds row and col numbers
    static const bool cross = false;     //adds cross in the middle
    


    rt::RayScanner rs = rt::RayScanner(rt::Screen(d, w, h, pW, pH, sPR, rpP));


    const int mirror = 1;
    const int diffuse = 2;
    rt::Floor f = rt::Floor(rt::Vec3D(0, -3, 0), rt::Vec3D(0.9, 0.4, 1), 0.5, mirror);
    // rt::Floor f = rt::Floor(rt::Vec3D(0, -3, 0), rt::Vec3D(0.99, 1, 0.99), 4, mirror);
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


    ch::duration<double, st::milli> timePassed;
    ch::time_point<Clock> start;
    ch::time_point<Clock> end;
    int count = 1;


    start = Clock::now();
    for(int i = 0; i < count; i++){

        st::time_t t = st::time(nullptr);
        char dateAndTime[25];
        std::strftime(dateAndTime, sizeof(dateAndTime), "%Y-%m-%d_%H-%M-%S", std::localtime(&t));

        st::string filename = "scenes/";
        filename.append(dateAndTime);
        filename += '_'
            + st::to_string(pW) + 'x' 
            + st::to_string(pH) + '-'
            + st::to_string(sPR*sPR) + 'x'
            + st::to_string(rpP);

        st::cout << "Start render of scene " << i+1 << ": " << filename;
        st::cout << "\nRays: " << static_cast<num>(pW)*pH*sPR*sPR*rpP << st::endl;

        if(multi){
            io.ppm(filename, rs.scan());
        } else{
            io.ppm(filename, rs.scanSingle());
        }

        st::cout << "Done with scene " << i+1 << ": " << filename << st::endl;

    }
    end = Clock::now();
    timePassed = end-start;

    st::cout << "Average over " << count << ": " << (timePassed/count).count()/1000 << "s\n";

    st::string stats = 
        st::to_string(pW) + 'x' 
        + st::to_string(pH) + ":\t" 
        + st::to_string(sPR*sPR) + 'x' 
        + st::to_string(rpP) + "\tn=" 
        + st::to_string(count) + "\ttime=" 
        + st::to_string(static_cast<int>((timePassed/count).count())) + "\tmulti="
        + st::to_string(multi);

    io.writeFile("scenes/Stats", stats);

    return 0;
}



