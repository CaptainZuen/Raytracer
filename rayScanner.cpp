#include "rayScanner.hpp"


namespace rayTracer{

RayScanner::RayScanner(num screenDistance, num screenWidth, num screenHeight, int pixelWidth, int pixelHeight):
    screenDistance(screenDistance),
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    pixelWidth(pixelWidth),
    pixelHeight(pixelHeight){    
}

void RayScanner::addObject(Object* object){
    objects.push_back(object);
}



scr RayScanner::scanGrey(){
    scr screen;

    for(int row = 0; row < pixelHeight; row++){
        st::vector<int> temp;

        for(int col = 0; col < pixelWidth; col++){
            
            // Gets the coordinate for the pixel
            //+ 1./pixels to centralize it, i.e. 8 pixels was -1 to 0.75, now -0.875 to 0.875 
            // y is negated because rows go from top to bottom
            num xStart = (col/static_cast<num>(pixelWidth))*screenWidth - screenWidth/2 + 0.5*(screenWidth/pixelWidth);
            num yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - screenHeight/2 + 0.5*(screenHeight/pixelHeight));
            
            Vec3D color = Ray(xStart, yStart, screenDistance, objects).scan();
            temp.push_back((color[0] + color[1] + color[2])/3*255);
        }
        screen.push_back(temp);
    }
    return screen;
}

scrRGB RayScanner::scanRGB(){
    scrRGB screen;

    for(int row = 0; row < pixelHeight; row++){
        st::vector<Vec3D> temp;

        for(int col = 0; col < pixelWidth; col++){
            
            num xStart = (col/static_cast<num>(pixelWidth))*screenWidth - screenWidth/2 + 0.5*(screenWidth/pixelWidth);
            num yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - screenHeight/2 + 0.5*(screenHeight/pixelHeight));
            
            temp.push_back(Ray(xStart, yStart, screenDistance, objects).scan()*255);
        }
        screen.push_back(temp);
    }
    return screen;
}
}