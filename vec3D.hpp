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


        friend Vec3D operator - (const Vec3D &v);
        friend Vec3D operator + (const Vec3D &v1, const Vec3D &v2);
        friend Vec3D operator - (const Vec3D &v1, const Vec3D &v2);
        friend Vec3D operator * (const Vec3D &v1, const Vec3D &v2);
        friend Vec3D operator / (const Vec3D &v1, const Vec3D &v2);
        friend Vec3D operator % (const Vec3D &v1, const Vec3D &v2);
        friend bool operator < (const Vec3D &v1, const Vec3D &v2);
        friend bool operator > (const Vec3D &v1, const Vec3D &v2);

    public:

        Vec3D(num x, num y, num z);
        Vec3D(num s);
        Vec3D(const Vec3D &v);
        Vec3D();
        
        num operator [] (int i) const;
        void setValue(int index, num value);


        void show (st::string label) const;
        void show (st::string label, num scalar) const;
        void show () const;

        
        num norm () const;                          //Length from zero
        Vec3D unit () const;                        //Vector of length 1
        num dot (const Vec3D &other) const;         //Dot product
        Vec3D cross (const Vec3D &other) const;     //Cross product

        Vec3D abs() const;                          //Absolute value      
        num angle(const Vec3D &v) const;            //returns angle in rad
        Vec3D rotX(const num angle) const;
        Vec3D rotY(const num angle) const;
        Vec3D rotZ(const num angle) const;

        Vec3D random() const;                       //return a random unit vector
};
}
