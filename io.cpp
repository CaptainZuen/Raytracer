#include "io.hpp"

IO::IO(){
}

void IO::terminal(scr const &screen, num const &aspect, bool const &numbers, bool const &cross) const{
    int pixelHeight = screen.size();
    int pixelWidth = screen[0].size();

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
            
            if(cross && row == pixelHeight/2){
                st::cout << '-';
            } else if(cross && col == static_cast<int>(pixelWidth*aspect/2)){
                st::cout << '|';
            } else{
                //prints the char relative to the brightness
                int const colAspect = static_cast<int>(col/aspect);
                num const temp = (screen[row][colAspect][0] + screen[row][colAspect][1] + screen[row][colAspect][2])/3;
                st::cout << chars[(temp*chars.size())-1];
            }
            
        }
        st::cout << '\n';
    }
}

void IO::ascii(st::string const &fileName, scr const &screen, num const &aspect, bool const &numbers, bool const &cross) const{
    st::ofstream file;
    file.open(fileName + ".txt", st::ios::out | st::ios::trunc);

    int pixelHeight = screen.size();
    int pixelWidth = screen[0].size();


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
            
            if(cross && row == pixelHeight/2){
                file << '-';
            } else if(cross && col == pixelWidth/2){
                file << '|';
            } else{
                file << chars[((screen[row][col][0] + screen[row][col][1] + screen[row][col][2])/3*chars.size())-1];
            }
        }
        file << '\n';
    }

    file.close();
}

void IO::ppm(st::string const &fileName, scr const &screen) const{
    st::ofstream file;
    file.open("scenes/" + fileName + ".ppm", st::ios::out | st::ios::trunc);

    int pixelHeight = screen.size();
    int pixelWidth = screen[0].size();

    //P3 ppm format (rgb in ascii), 255 being max value
    file << "P3\n" << pixelWidth << ' ' << pixelHeight << "\n255\n\n";

    for(int row = 0; row < pixelHeight; row++){

        for(int col = 0; col < pixelWidth; col++){

            file    << static_cast<int>(screen[row][col][0]*255.999) << ' ' 
                    << static_cast<int>(screen[row][col][1]*255.999) << ' ' 
                    << static_cast<int>(screen[row][col][2]*255.999) << '\n';
            
        }
        file << '\n';
    }

    file.close();
}

void IO::ppm(st::string const &fileName, scrFut const &screen) const{
    st::ofstream file;
    file.open("scenes/" + fileName + ".ppm", st::ios::out | st::ios::trunc);

    int pixelHeight = screen.size();
    int pixelWidth = screen[0].size();

    //P3 ppm format (rgb in ascii), 255 being max value
    file << "P3\n" << pixelWidth << ' ' << pixelHeight << "\n255\n\n";

    int old = -1;
    st::cout << "Printing image\n";
    
    for(int row = 0; row < pixelHeight; row++){

        int progress = static_cast<int>(static_cast<num>(row)/pixelHeight*100);

        if(progress > old){
            st::cout << "Progress: " << progress << "%\n";
            old = progress;
        }
        for(int col = 0; col < pixelWidth; col++){
            rt::Vec3D temp = screen[row][col].get();
            file    << static_cast<int>(temp[0]*255.999) << ' ' 
                    << static_cast<int>(temp[1]*255.999) << ' ' 
                    << static_cast<int>(temp[2]*255.999) << '\n';
            
        }
        file << '\n';
    }

    file.close();
}

void IO::file(st::string const &fileName, st::string const &text) const{
    st::ofstream file;
    file.open(fileName + ".txt", st::ios::out | st::ios::app);
    file << text << '\n';

    file.close();
}