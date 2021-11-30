/*
includes overal?
ray en objects includen elkaar?
hoe netjes? liever dubbel voor duidelijkheid?
ifndef??

Read from file
ppm to png
multithreading
vec3D rotates
inline!!

Object* sortedX
Object* sortedY
Object* sortedZ


*/


#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <future>   //throws mult def exception when included elsewhere

#include "vec3D.hpp"


static const num inf = st::numeric_limits<num>::infinity();
static const double pi = 3.1415926535897932385;

#include "ray.hpp"

namespace rt = rayTracer;
