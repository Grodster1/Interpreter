#ifndef CUBOID_HH
#define CUBOID_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractMobileObj.hh"
#include "Vector3D.hh"
/*!
 * \file
 * \brief Definicja klasy Cuboid
 *
 * Plik zawiera definicję klasy Cuboid ...
 */

/*!
 * \brief Reprezentuje obiekt na scenie
 *
 *  Klasa modeluj47e ...
 */


class Cuboid: public AbstractMobileObj{
private:
    Vector3D _Ang_RPY;
    Vector3D _Position_m;
    std::string _ObjName;

    //Poniżej pola związane z prasowaniem XMLa
    Vector3D _Shift, _Scale, _RGB;

public:
    Cuboid();
    ~Cuboid();

    virtual void SetName(const char* sName) override {_ObjName = sName;};
    virtual void SetRPY(const Vector3D &RPY) override {_Ang_RPY = RPY;};
    virtual void SetPosition_m(const Vector3D &rPos) override {_Position_m = rPos;};
    void SetScale(const Vector3D & scale) {_Scale = scale;}
    void SetShift(const Vector3D & shift) {_Shift = shift;}
    void SetRGB(const Vector3D & rgb) {_RGB = rgb;}

    virtual const std::string & GetName() const override {return _ObjName;};
    virtual const Vector3D & GetRPY() const override {return _Ang_RPY;};
    virtual const Vector3D & GetPosition_m() const override {return _Position_m;};
    const Vector3D & GetScale() const {return _Scale;}
    const Vector3D & GetShift() const {return _Shift;}
    const Vector3D & GetRGB() const {return _RGB;}  
};
#endif