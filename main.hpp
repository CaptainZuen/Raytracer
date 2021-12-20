/*
includes overal?
ray en objects includen elkaar?
hoe netjes? liever dubbel voor duidelijkheid?
ifndef??

-multithreading
-ray depth dynamic
-vec3D rotates
    - mix mirr and diff reflection
    - add mirr and diff in one ray
    - rotate ray by...

Read from file
ppm to png
inline!!
new iets()
emplace back


Object* sortedX
Object* sortedY
Object* sortedZ
boxes /intersects edge to next box?


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
#include <random>

#define num float
namespace st = std;
typedef st::mt19937 MyRNG;
typedef st::chrono::high_resolution_clock Clock;

static const num inf = st::numeric_limits<num>::infinity();
static const double pi = 3.1415926535897932385;

namespace rayTracer{}
namespace rt = rayTracer;
