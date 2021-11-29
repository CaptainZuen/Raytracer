#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <cmath>

#define num float
namespace st = std;

namespace rayTracer{

class Vec3D {
    protected:
        num c[3];


        friend Vec3D operator - (Vec3D const &v);
        friend Vec3D operator + (Vec3D const &v1, Vec3D const &v2);
        friend Vec3D operator - (Vec3D const &v1, Vec3D const &v2);
        friend Vec3D operator * (Vec3D const &v1, Vec3D const &v2);
        friend Vec3D operator / (Vec3D const &v1, Vec3D const &v2);
        friend Vec3D operator % (Vec3D const &v1, Vec3D const &v2);
        friend bool operator < (Vec3D const &v1, Vec3D const &v2);
        friend bool operator > (Vec3D const &v1, Vec3D const &v2);

    public:

        Vec3D(num x, num y, num z);
        Vec3D(num s);
        Vec3D(Vec3D const &v);
        Vec3D();
        
        num operator [] (int i) const;
        void setValue(int index, num value);


        void show (st::string label) const;
        void show (st::string label, num scalar) const;
        void show () const;

        
        num norm () const;                          //Length from zero
        Vec3D unit () const;                        //Vector of length 1
        num dot (Vec3D const &other) const;         //Dot product
        Vec3D cross (Vec3D const &other) const;     //Cross product

        Vec3D abs() const;                          //Absolute value      
        num angle(Vec3D const &v) const;            //returns angle in rad
        Vec3D rotX(num const angle) const;
        Vec3D rotY(num const angle) const;
        Vec3D rotZ(num const angle) const;

        Vec3D random() const;                       //return a random unit vector
};
}
