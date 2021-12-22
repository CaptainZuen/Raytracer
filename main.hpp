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
live preview?

~~ppm to png
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
#include <list>
#include <string> 
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <chrono>
#include <random>

#define num float
namespace st = std;
namespace rayTracer{}
namespace rt = rayTracer;
namespace ch = st::chrono;

typedef st::mt19937 MyRNG;
typedef ch::high_resolution_clock Clock;

static const num inf = st::numeric_limits<num>::infinity();
static const double pi = 3.1415926535897932385;


