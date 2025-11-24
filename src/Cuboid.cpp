#include "Cuboid.hh"

Cuboid::Cuboid(){
    _Ang_RPY[0] = 0.0;
    _Ang_RPY[1] = 0.0;
    _Ang_RPY[2] = 0.0;

    _Scale[0] = 1.0;
    _Scale[1] = 1.0;
    _Scale[2] = 1.0;

    _RGB[0] = 128.0;
    _RGB[1] = 128.0;
    _RGB[2] = 128.0;
}

Cuboid::~Cuboid(){}