#pragma once
#include <fstream>
// #include <png.h>

#include "main.hpp"
#include "rayScanner.hpp"


class IO{
    protected:
        const st::string chars = " .:-=+*#%@";

    public:
        IO();

        void terminal(const rndr &render, const num &aspect, const bool &numbers, const bool &cross) const; //add row and col numbers and/or cross in the middle
        void ascii(const st::string &fileName, const rndr &render, const num &aspect, const bool &numbers, const bool &cross) const;
        void ppm(const st::string &fileName, const rndr &render) const;
        // void png(const char *fileName, const scr &screen) const;

        void writeFile(const st::string &fileName, const st::string &text) const;
};