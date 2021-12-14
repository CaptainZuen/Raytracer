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
        // num* c = new num[3];
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
        Vec3D(num* s);
        Vec3D();

        Vec3D(const Vec3D &v);
        // Vec3D(Vec3D &&v);
        // ~Vec3D();
        
        num operator [] (int i) const;
        num& operator [] (int i);

        Vec3D& operator = (const Vec3D &v);
        // Vec3D& operator = (Vec3D &&v);

        Vec3D& operator += (const Vec3D &v);
        Vec3D& operator *= (const Vec3D &v);
        Vec3D& operator /= (const Vec3D &v); 

        Vec3D operator - ();
        Vec3D operator - (const Vec3D &v);
        Vec3D operator + (const Vec3D &v);
        Vec3D operator * (const Vec3D &v);
        Vec3D operator / (const Vec3D &v);
        Vec3D operator % (const Vec3D &v);

        Vec3D& setValue(const num value);


        void show (st::string label) const;
        void show (st::string label, num scalar) const;
        void show () const;

        
        num norm () const;                          //Length from zero
        Vec3D& unit ();                             //Vector of length 1
        num dot (const Vec3D &other) const;         //Dot product
        Vec3D& cross (const Vec3D &other);          //Cross product

        Vec3D& abs();                               //Absolute value      
        num angle(const Vec3D &v) const;            //returns angle in rad
        Vec3D& rotX(const num angle);
        Vec3D& rotY(const num angle);
        Vec3D& rotZ(const num angle);

        Vec3D& random();                            //return a random unit vector
};
}
