#include "rayScanner.hpp"


namespace rayTracer{

RayScanner::RayScanner(){}



void RayScanner::addObject(Object* object){
    objects.push_back(object);
}


scr RayScanner::scan(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel){
    scr screen;
    // scr screen[pixelHeight][pixelWidth];

    bool const antiAliasing = raysPPixel > 1;
    num const halfPixelWidth = 0.5*(screenWidth/pixelWidth);
    num const halfPixelHeight = 0.5*(screenHeight/pixelHeight);
    num const offsetX = screenWidth/2 + halfPixelWidth;
    num const offsetY = screenHeight/2 + halfPixelHeight;

    int old = -1;

    for(int row = 0; row < pixelHeight; row++){
        st::vector<Vec3D> temp;
        // st::vector<Vec3D> temp[pixelWidth];
        
        int progress = static_cast<int>(static_cast<num>(row)/pixelHeight*100);

        if(progress > old){
            st::cout << "Progress: " << progress << "%\n";
            old = progress;
        }



        for(int col = 0; col < pixelWidth; col++){
            
            num xStart = (col/static_cast<num>(pixelWidth))*screenWidth - offsetX;
            num yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - offsetY);
            
            if(antiAliasing){
                Vec3D pixelColors = Vec3D();
                for(int i = 0; i < raysPPixel; i++){
                    Vec3D random = pixelColors.random();
                    num x = xStart + halfPixelWidth * random[0];
                    num y = yStart + halfPixelHeight * random[1];
                    // pixelColors = pixelColors + Ray(x, y, screenDistance, objects).scan(bounceLimit);
                    pixelColors = pixelColors + Ray(x, y, screenDistance).scan(objects, bounceLimit);
                }
                temp.push_back(pixelColors/raysPPixel);
            } else{
                // temp.push_back(Ray(xStart, yStart, screenDistance, objects).scan(bounceLimit));
                temp.push_back(Ray(xStart, yStart, screenDistance).scan(objects, bounceLimit));

            }

            // for(all){
            //     async
            // }
            // for(all){
            //     temp.emplace_back(future)
            // }


        }
        screen.push_back(temp);
    }

    st::cout << "Done!\n";
    return screen;
}
}