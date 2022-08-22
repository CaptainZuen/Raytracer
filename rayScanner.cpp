#include "rayScanner.hpp"
#include <future>


namespace rayTracer{

RayScanner::RayScanner(Screen scr):
    scr (scr){
}


void RayScanner::addObject(Object* object){
    objects.push_back(object);
}



Vec3D& rayScan(Ray ray, VPO& objects, Vec3D& color, int depth){
    if(depth <= 0){
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        return color;
    }

    ray.tMax = inf;
    Object* current = NULL;
    for(auto &object: objects){
        num t = object->hit(ray);
        if(t > ray.tMin && t < ray.tMax){
            ray.tMax = t;
            current = object;
        }
    }
    if(current != NULL){
        ray.sup = ray.at(ray.tMax);
        ray.dir = current->bounce(ray.dir, ray.sup);
        color *= current->getColor(); 
        if(color < 0.003906) return color; 
        rayScan(ray, objects, color, --depth);      
        return color;
    }

    color[0] *= (1 - ((ray.dir[1] + 1)/2) * 0.5);
    color[1] *= (1 - ((ray.dir[1] + 1)/2) * 0.3);
    return color;
}


Vec3D pixelScan(VPO& objects, Screen scr, const num xStart, const num yStart, const int depthLimit){
    Vec3D pixelColors;

        for(int i = 0; i < scr.raysPPixel; i++){
            Vec3D vec3D = Vec3D().random();

            const num x = xStart + scr.halfpixelsWide * vec3D[0];
            const num y = yStart + scr.halfpixelsHigh * vec3D[1];

            vec3D = Vec3D(1);
            pixelColors += rayScan(Ray(x, y, scr.distance), objects, vec3D, depthLimit);
        }
    
    return pixelColors/scr.raysPPixel;
}




rndr RayScanner::scanSingle(){
    rndr render;
    render.reserve(scr.height);


    rng = new MyRNG;
    rng->seed(time(nullptr));
    Vec3D random;

    int old = -1;

    for(int row = 0; row < scr.pixelsHigh; row++){
        st::vector<Vec3D> temp;
        temp.reserve(scr.width);
        
        int progress = static_cast<int>(static_cast<num>(row)/scr.pixelsHigh*100);
        if(progress > old){
            st::cout << "Progress: " << progress << "%\n";
            old = progress;
        }



        for(int col = 0; col < scr.pixelsWide; col++){
            
            num xStart = (col/static_cast<num>(scr.pixelsWide))*scr.width - scr.offsetX;
            num yStart = -((row/static_cast<num>(scr.pixelsHigh))*scr.height - scr.offsetY);
            
            temp.push_back(pixelScan(objects, scr, xStart, yStart, depthLimit));

        }
        render.push_back(temp);
    }

    st::cout << "Done!\n";
    return render;
}



st::vector<Vec3D> rowScan(VPO objects, const num depthLimit, Screen scr, const int row, MyRNG* threadRNG){
    
    rng = threadRNG;
    Vec3D random;

    st::vector<Vec3D> temp;
    temp.reserve(scr.width);


    for(int col = 0; col < scr.pixelsWide; col++){
        
        const num xStart = (col/static_cast<num>(scr.pixelsWide))*scr.width - scr.offsetX;
        const num yStart = -((row/static_cast<num>(scr.pixelsHigh))*scr.height - scr.offsetY);
        
        temp.push_back(pixelScan(objects, scr, xStart, yStart, depthLimit));

    }
    return temp;
}

rndr RayScanner::scan(){
    rndr render;
    render.reserve(scr.pixelsHigh);

    st::vector<st::shared_future<st::vector<Vec3D>>> rowFutures;
    rowFutures.reserve(scr.pixelsHigh);

    st::cout << "Starting threads" << st::endl;

    int old = -1;
    const ch::time_point<Clock> randTime = Clock::now();
    
    for(int row = 0; row < scr.pixelsHigh; row++){

        int progress = static_cast<int>(static_cast<num>(row)/scr.pixelsHigh*100);
        if(progress > old){
            st::cout << "Progress: " << progress << '%' << st::endl;
            old = progress;
        }

        MyRNG::result_type seed = ch::duration_cast<ch::microseconds>(Clock::now() - randTime).count();
        MyRNG* threadRNG = new MyRNG;
        threadRNG->seed(seed);

        rowFutures.push_back(st::async(rowScan, objects, depthLimit, scr, row, threadRNG));
    }



    st::cout << "Getting results----------------------------------------" << st::endl;
    old = -1;
    
    for(int row = 0; row < scr.pixelsHigh; row++){

        int progress = static_cast<int>(static_cast<num>(row)/scr.pixelsHigh*100);
        if(progress > old){
            st::cout << "Progress: " << progress << '%' << st::endl;
            old = progress;
        }

        render.push_back(rowFutures[row].get());
    }
    st::cout << "Done!\n";
    return render;
    
}


}

