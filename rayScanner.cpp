#include "rayScanner.hpp"
 

namespace rayTracer{

RayScanner::RayScanner(){}



void RayScanner::addObject(Object* object){
    objects.push_back(object);
}



scr RayScanner::scanSingle(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel){
    scr screen;
    screen.reserve(screenHeight);

    num const halfPixelWidth = 0.5*(screenWidth/pixelWidth);
    num const halfPixelHeight = 0.5*(screenHeight/pixelHeight);
    num const offsetX = screenWidth/2 + halfPixelWidth;
    num const offsetY = screenHeight/2 + halfPixelHeight;

    int old = -1;

    for(int row = 0; row < pixelHeight; row++){
        st::vector<Vec3D> temp;
        temp.reserve(screenWidth);
        
        int progress = static_cast<int>(static_cast<num>(row)/pixelHeight*100);

        if(progress > old){
            st::cout << "Progress: " << progress << "%\n";
            old = progress;
        }



        for(int col = 0; col < pixelWidth; col++){
            
            num xStart = (col/static_cast<num>(pixelWidth))*screenWidth - offsetX;
            num yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - offsetY);
            
            Vec3D pixelColors = Vec3D();
            for(int i = 0; i < raysPPixel; i++){
                Vec3D random = pixelColors.random();
                num x = xStart + halfPixelWidth * random[0];
                num y = yStart + halfPixelHeight * random[1];
                pixelColors = pixelColors + Ray(x, y, screenDistance).scan(objects, bounceLimit);
            }
            temp.push_back(pixelColors/raysPPixel);

        }
        screen.push_back(temp);
    }

    st::cout << "Done!\n";
    return screen;
}



st::vector<Vec3D> rowScan(VPO objects, num const bounceLimit, num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel, int const row){
    num static const halfPixelWidth = 0.5*(screenWidth/pixelWidth);
    num static const halfPixelHeight = 0.5*(screenHeight/pixelHeight);
    num static const offsetX = screenWidth/2 + halfPixelWidth;
    num static const offsetY = screenHeight/2 + halfPixelHeight;
    
    
    st::vector<Vec3D> temp;
    temp.reserve(screenWidth);


    for(int col = 0; col < pixelWidth; col++){
        
        num xStart = (col/static_cast<num>(pixelWidth))*screenWidth - offsetX;
        num yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - offsetY);
        
        Vec3D pixelColors = Vec3D();
        for(int i = 0; i < raysPPixel; i++){
            Vec3D random = pixelColors.random();
            num x = xStart + halfPixelWidth * random[0];
            num y = yStart + halfPixelHeight * random[1];
            pixelColors = pixelColors + Ray(x, y, screenDistance).scan(objects, bounceLimit);
        }
        temp.push_back(pixelColors/raysPPixel);

    }
    return temp;
}

scr RayScanner::scan(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel){
    
    int old = -1;

    scr screen;
    screen.reserve(screenHeight);

    st::cout << "Starting threads\n";

    st::vector<st::shared_future<st::vector<Vec3D>>> rowFutures;
    for(int row = 0; row < pixelHeight; row++){
        int progress = static_cast<int>(static_cast<num>(row)/pixelHeight*100);

        if(progress > old){
            st::cout << "Progress: " << progress << "%\n";
            old = progress;
        }

        rowFutures.push_back(st::async(rowScan, objects, bounceLimit, screenDistance, screenWidth, screenHeight, pixelWidth, pixelHeight, raysPPixel, row));
    }

    old = -1;

    for(int row = 0; row < pixelHeight; row++){
        int progress = static_cast<int>(static_cast<num>(row)/pixelHeight*100);

        if(progress > old){
            st::cout << "Progress: " << progress << "%\n";
            old = progress;
        }

        screen.push_back(rowFutures[row].get());
    }
    st::cout << "Done!\n";
    return screen;
    
}
}