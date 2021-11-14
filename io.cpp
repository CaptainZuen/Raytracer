#include "io.hpp"

IO::IO(){
}

void IO::print(scr const &screen, num const aspect, bool const numbers, bool const cross){
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

void IO::print(st::string fileName, scr const &screen, num const aspect, bool const numbers, bool const cross){
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

void IO::ppm(st::string fileName, scrRGB const &screen){
    st::ofstream file;
    file.open(fileName + ".ppm", st::ios::out | st::ios::trunc);

    int pixelHeight = screen.size();
    int pixelWidth = screen[0].size();

    //P3 ppm format (rgb in ascii), 255 being max value
    file << "P3\n" << pixelWidth << ' ' << pixelHeight << "\n255\n\n";

    for(int row = 0; row < pixelHeight; row++){

        for(int col = 0; col < pixelWidth; col++){

            file << screen[row][col][0] << ' ' << screen[row][col][1] << ' ' << screen[row][col][2] << '\n';
            
        }
        file << '\n';
    }

    file.close();
}