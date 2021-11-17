#pragma once
#include <fstream>

#include "main.hpp"
#include "rayScanner.hpp"


class IO{
    protected:
        st::string chars = " .:-=+*#%@";

    public:
        IO();

        void print(scr const &screen, num const aspect, bool const numbers, bool const cross); //add row and col numbers and/or cross in the middle
        void print(st::string const fileName, scr const &screen, num const aspect, bool const numbers, bool const cross);

        void ppm(st::string const fileName, scrRGB const &screen);
};