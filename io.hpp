#pragma once
#include <fstream>

#include "main.hpp"
#include "rayScanner.hpp"


class IO{
    protected:
        const st::string chars = " .:-=+*#%@";

    public:
        IO();

        void terminal(scr const &screen, num const &aspect, bool const &numbers, bool const &cross) const; //add row and col numbers and/or cross in the middle
        void ascii(st::string const &fileName, scr const &screen, num const &aspect, bool const &numbers, bool const &cross) const;
        void ppm(st::string const &fileName, scr const &screen) const;
        void ppm(st::string const &fileName, scrFut const &screen) const;

        void file(st::string const &fileName, st::string const &text) const;
};