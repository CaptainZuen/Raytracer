#include "rayScanner.hpp"


namespace rayTracer{

RayScanner::RayScanner(){}



void RayScanner::addObject(Object* object){
    objects.push_back(object);
}



scr RayScanner::scanGrey(num screenDistance, num screenWidth, num screenHeight, int pixelWidth, int pixelHeight){
    scr screen;

    for(int row = 0; row < pixelHeight; row++){
        st::vector<int> temp;

        for(int col = 0; col < pixelWidth; col++){
            
            // Gets the coordinate for the pixel
            //+ 1./pixels to centralize it, i.e. 8 pixels was -1 to 0.75, now -0.875 to 0.875 
            // y is negated because rows go from top to bottom
            num xStart = (col/static_cast<num>(pixelWidth))*screenWidth - screenWidth/2 + 0.5*(screenWidth/pixelWidth);
            num yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - screenHeight/2 + 0.5*(screenHeight/pixelHeight));
            
            Vec3D color = Ray(xStart, yStart, screenDistance, objects).scan(0);
            temp.push_back(static_cast<int>((color[0] + color[1] + color[2])/3*255));
        }
        screen.push_back(temp);
    }
    return screen;
}

scrRGB RayScanner::scanRGB(num const screenDistance, num const screenWidth, num const screenHeight, int const pixelWidth, int const pixelHeight, int const raysPPixel){
    scrRGB screen;
    bool const antiAliasing = raysPPixel > 0;

    int old = -1;

    for(int row = 0; row < pixelHeight; row++){
        st::vector<Vec3D> temp;
        
        int progress = static_cast<int>(static_cast<num>(row)/pixelHeight*100);
    
        if(progress > old){
            st::cout << "Progress: " << progress << "%\n";
            old = progress;
        }

        for(int col = 0; col < pixelWidth; col++){
            
            num xStart = (col/static_cast<num>(pixelWidth))*screenWidth - screenWidth/2 + 0.5*(screenWidth/pixelWidth);
            num yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - screenHeight/2 + 0.5*(screenHeight/pixelHeight));
            
            if(antiAliasing){
                Vec3D rayColors = Vec3D();
                for(int i = 0; i < raysPPixel; i++){
                    Vec3D random = rayColors.random();
                    num x = xStart + 0.5*(screenWidth/pixelWidth) * random[0];
                    num y = yStart + 0.5*(screenWidth/pixelWidth) * random[1];
                    rayColors = rayColors + Ray(x, y, screenDistance, objects).scan(0);
                }
                temp.push_back(rayColors/raysPPixel);
            } else{
                temp.push_back(Ray(xStart, yStart, screenDistance, objects).scan(0));

            }
        }
        screen.push_back(temp);
    }

    st::cout << "Done!\n";
    return screen;
}
}