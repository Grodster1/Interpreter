#include "Cuboid.hh"
#include <sstream>
#include <iomanip>

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

std::string Cuboid::GetStateDesc() const
{
    std::stringstream ss;
    
    auto formatVec = [](const Vector3D& v) -> std::string {
        std::stringstream s;
        s << "(" << v[0] << "," << v[1] << "," << v[2] << ")";
        return s.str();
    };

    ss << "UpdateObj";
    ss << " Name=" << _ObjName; 
    ss << " Trans_m=" << formatVec(_Position_m);
    ss << " RotXYZ_deg=" << formatVec(_Ang_RPY);
    ss << " Scale=" << formatVec(_Scale);
    ss << " RGB=" << formatVec(_RGB);
    ss << "\n";

    return ss.str();
}


Cuboid::~Cuboid(){}