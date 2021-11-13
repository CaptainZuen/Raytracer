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



scr RayScanner::scan(){
    scr screen;

    for(int row = 0; row < pixelHeight; row++){
        st::vector<int> temp;

        for(int col = 0; col < pixelWidth; col++){
            
            // Gets the coordinate for the pixel
            //+ 1./pixels to centralize it, i.e. 8 pixels was -1 to 0.75, now -0.875 to 0.875 
            // y is negated because rows go from top to bottom
            num xStart = (col/static_cast<num>(pixelWidth))*screenWidth - screenWidth/2 + 0.5*(screenWidth/pixelWidth);
            num yStart = -((row/static_cast<num>(pixelHeight))*screenHeight - screenHeight/2 + 0.5*(screenHeight/pixelHeight));
            
            if(Ray(xStart, yStart, screenDistance, objects).scan()){
                temp.push_back(255);
            }
            else {
                temp.push_back(0);
            }
        }
        screen.push_back(temp);
    }
    return screen;
}

void RayScanner::print(scr screen, num aspect, bool numbers, bool cross){

    if(numbers){
        st::cout << "\t ";
        for(int i = 0; i < st::to_string(pixelWidth-1).size(); i++){
            for(int col = 0; col < pixelWidth*aspect; col+=2){
                st::string s = st::to_string(static_cast<int>(col/aspect));
                st::cout << s[i] << ' ';
                s = "           "; //to clear the memory. 3rd digit would remain
            }
            st::cout << "\n\t ";
        }
        for(int col = 0; col < pixelWidth*aspect; col+=2){
            st::cout << "_ ";
        }
        st::cout << '\n';
    }


    for(int row = 0; row < pixelHeight; row++){

        if(numbers) st::cout << row << "\t|";

        for(int col = 0; col < pixelWidth*aspect; col++){
            
            if(cross){
                if(row == pixelHeight/2){
                    st::cout << '-';
                } else if(col == static_cast<int>(pixelWidth*aspect/2)){
                    st::cout << '|';
                } else{
                    st::cout << chars[(screen[row][static_cast<int>(col/aspect)]/255*chars.size())-1];
                }
            } else {
                //prints the char relative to the brightness
                st::cout << chars[(screen[row][static_cast<int>(col/aspect)]/255*chars.size())-1];
            }
        }
        st::cout << '\n';
    }
}

void RayScanner::print(st::string fileName, num aspect, scr screen, bool numbers, bool cross){
    ofstream file;
    file.open(fileName, ios::out | ios::trunc);


    if(numbers){
        file << "\t ";
        for(int i = 0; i < st::to_string(pixelWidth-1).size(); i++){
            for(int col = 0; col < pixelWidth; col+=2){
                st::string s = st::to_string(col);
                file << s[i] << ' ';
                s = "           "; //to clear the memory. 3rd digit would remain
            }
            file << "\n\t ";
        }
        for(int col = 0; col < pixelWidth; col+=2){
            file << "_ ";
        }
        file << '\n';
    }


    for(int row = 0; row < pixelHeight; row++){

        if(numbers) file << row << "\t|";

        for(int col = 0; col < pixelWidth; col++){
            
            if(cross){
                if(row == pixelHeight/2){
                    file << '-';
                } else if(col == pixelWidth/2){
                    file << '|';
                } else{
                    file << chars[(screen[row][col]/255*chars.size())-1];
                }
            } else {
                //prints the char relative to the brightness
                file << chars[(screen[row][col]/255*chars.size())-1];
            }
        }
        file << '\n';
    }

    file.close();
}
}