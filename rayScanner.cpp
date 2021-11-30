#include "rayScanner.hpp"
 

namespace rayTracer{

RayScanner::RayScanner(){}



void RayScanner::addObject(Object* object){
    objects.push_back(object);
}



scr RayScanner::scan(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel){
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



Vec3D pixelScan(VPO objects, int const bounceLimit, num const screenDistance, int const raysPPixel, num const xStart, num const yStart, num const halfPixelWidth, num const halfPixelHeight){
    Vec3D pixelColors = Vec3D();

    for(int i = 0; i < raysPPixel; i++){
        Vec3D random = pixelColors.random();
        num x = xStart + halfPixelWidth * random[0];
        num y = yStart + halfPixelHeight * random[1];
        pixelColors = pixelColors + Ray(x, y, screenDistance).scan(objects, bounceLimit);
    }
    return pixelColors/raysPPixel;
}

scrFut RayScanner::scanMulti(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel){
    
    num const halfPixelWidth = 0.5*(screenWidth/pixelWidth);
    num const halfPixelHeight = 0.5*(screenHeight/pixelHeight);
    num const offsetX = screenWidth/2 + halfPixelWidth;
    num const offsetY = screenHeight/2 + halfPixelHeight;
    int old = -1;

    scrFut futures;
    futures.reserve(screenHeight);

    st::cout << "Starting threads\n";

    for(int row = 0; row < pixelHeight; row++){
        int progress = static_cast<int>(static_cast<num>(row)/pixelHeight*100);

        if(progress > old){
            st::cout << "Progress: " << progress << "%\n";
            old = progress;
        }

        st::vector<st::shared_future<Vec3D>> temp;
        temp.reserve(screenWidth);

        for(int col = 0; col < pixelWidth; col++){
            num const xStart = (col/static_cast<num>(pixelWidth))*screenWidth - offsetX;
            num const yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - offsetY);
            
            temp.push_back(st::async(pixelScan, objects, bounceLimit,screenDistance, raysPPixel, xStart, yStart, halfPixelWidth, halfPixelHeight));
        } 
        futures.push_back(temp);
    }

    return futures;
}

Vec3D rayScan(VPO objects, num const bounceLimit, num const screenDistance, num const x, num const y){
    return Ray(x, y, screenDistance).scan(objects, bounceLimit);
}

scr RayScanner::scanTest(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel){
    
    num const halfPixelWidth = 0.5*(screenWidth/pixelWidth);
    num const halfPixelHeight = 0.5*(screenHeight/pixelHeight);
    num const offsetX = screenWidth/2 + halfPixelWidth;
    num const offsetY = screenHeight/2 + halfPixelHeight;
    int old = -1;

    scr screen;
    screen.reserve(screenHeight);

    st::cout << "Starting threads\n";

    for(int row = 0; row < pixelHeight; row++){
        int progress = static_cast<int>(static_cast<num>(row)/pixelHeight*100);

        if(progress > old){
            st::cout << "Progress: " << progress << "%\n";
            old = progress;
        }

        st::vector<Vec3D> temp;
        temp.reserve(screenWidth);

        for(int col = 0; col < pixelWidth; col++){
            num const xStart = (col/static_cast<num>(pixelWidth))*screenWidth - offsetX;
            num const yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - offsetY);
            
            // temp.push_back(st::async(pixelScan, objects, bounceLimit,screenDistance, raysPPixel, xStart, yStart, halfPixelWidth, halfPixelHeight));
            
            st::vector<st::shared_future<Vec3D>> pixelColors;
            Vec3D color;
            for(int i = 0; i < raysPPixel; i++){
                Vec3D random = color.random();
                num x = xStart + halfPixelWidth * random[0];
                num y = yStart + halfPixelHeight * random[1];
                
                pixelColors.push_back(st::async(rayScan, objects, bounceLimit, screenDistance, x, y));
            }
            for(int i = 0; i < raysPPixel; i++){
                color = color + pixelColors[i].get();
            }
            temp.push_back(color/raysPPixel);
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

scr RayScanner::scanTestRow(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel){
    
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