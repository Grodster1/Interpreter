#include "Cuboid.hh"

Cuboid::Cuboid() : _Roll(0.0), _Pitch(0.0), _Yaw(0.0){
    _Scale[0] = 1.0;
    _Scale[1] = 1.0;
    _Scale[2] = 1.0;

    _RGB[0] = 128.0;
    _RGB[1] = 128.0;
    _RGB[2] = 128.0;
}

double Cuboid::GetAng_Roll_deg() const{
    return _Roll;
}

double Cuboid::GetAng_Pitch_deg() const{
    return _Pitch;
}

double Cuboid::GetAng_Yaw_deg() const{
    return _Yaw;
}

void Cuboid::SetAng_Roll_deg(double Ang_Roll_deg){
    _Roll = Ang_Roll_deg;
}

void Cuboid::SetAng_Pitch_deg(double Ang_Pitch_deg){
    _Pitch = Ang_Pitch_deg;
}

void Cuboid::SetAng_Yaw_deg(double Ang_Yaw_deg){
    _Yaw = Ang_Yaw_deg;
}

const Vector3D & Cuboid::GetPosition_m() const{
    return _Position_m;
}

void Cuboid::SetPosition_m(const Vector3D &rPos){
    _Position_m = rPos;
}

void Cuboid::SetName(const char* sName){
    _ObjName = sName;
}

const std::string & Cuboid::GetName() const{
    return _ObjName;
}

Cuboid::~Cuboid(){}