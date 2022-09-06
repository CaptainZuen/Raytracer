#include "../io.hpp"

IO::IO(){}


void IO::terminal(const rndr &render, const num &aspect, const bool &numbers, const bool &cross) const{
    int pixelHeight = render.size();
    int pixelWidth = render[0].size();

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
                const int colAspect = static_cast<int>(col/aspect);
                const num temp = (render[row][colAspect][0] + render[row][colAspect][1] + render[row][colAspect][2])/3;
                st::cout << chars[(temp*chars.size())-1];
            }
            
        }
        st::cout << '\n';
    }
}

void IO::ascii(const st::string &fileName, const rndr &render, const num &aspect, const bool &numbers, const bool &cross) const{
    st::ofstream file;
    file.open(fileName + ".txt", st::ios::out | st::ios::trunc);

    int pixelHeight = render.size();
    int pixelWidth = render[0].size();


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
                file << chars[((render[row][col][0] + render[row][col][1] + render[row][col][2])/3*chars.size())-1];
            }
        }
        file << '\n';
    }

    file.close();
}

void IO::ppm(const st::string &fileName, const rndr &render) const{
    st::ofstream file(fileName + ".ppm", st::ios::out | st::ios::trunc);
    if(file.is_open()){

        int pixelHeight = render.size();
        int pixelWidth = render[0].size();

        //P3 ppm format (rgb in ascii), 255 being max value
        file << "P3\n" << pixelWidth << ' ' << pixelHeight << "\n255\n";

        for(int row = 0; row < pixelHeight; row++){

            for(int col = 0; col < pixelWidth; col++){

                file    << static_cast<uint_fast16_t>(render[row][col][0]*255.999) << ' ' 
                        << static_cast<uint_fast16_t>(render[row][col][1]*255.999) << ' ' 
                        << static_cast<uint_fast16_t>(render[row][col][2]*255.999) << '\n';
            }
            file << '\n';
        }
        file.close();

    } else {
        st::cout << "Couldn't create: " << fileName << st::endl;
    }
}

// void IO::png(const char *fileName, const rndr &render) const{
//     int pixelHeight = render.size();
//     int pixelWidth = render[0].size();

//     FILE *file = fopen(fileName, "wb");
//     if (!file){
//         st::cout << "nope" << st::endl;
//         return;
//     }

//     // error pointers tbi
//     png_structp png_ptr = png_create_write_struct
//         (PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
//     if (!png_ptr)
//        st::cout << "nope" << st::endl;
//         return;

//     png_infop info_ptr = png_create_info_struct(png_ptr);
//     if (!info_ptr){
//         png_destroy_write_struct(&png_ptr,
//             (png_infopp)NULL);
//         st::cout << "nope" << st::endl;
//         return;
//     }

//     for(int row = 0; row < pixelHeight; row++){

//         for(int col = 0; col < pixelWidth; col++){

            
//         }
//     }
    

    
// }


void IO::writeFile(const st::string &fileName, const st::string &text) const{
    st::ofstream file;
    file.open(fileName + ".txt", st::ios::out | st::ios::app);
    file << text << '\n';

    file.close();
}