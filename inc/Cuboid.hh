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
    double _Roll, _Pitch, _Yaw;
    Vector3D _Position_m;
    std::string _ObjName;

    //Poniżej pola związane z prasowaniem XMLa
    Vector3D _Shift, _Scale, _RGB;

public:
    Cuboid();
    ~Cuboid();

    virtual double GetAng_Roll_deg() const override;
    virtual double GetAng_Pitch_deg() const override;
    virtual double GetAng_Yaw_deg() const override;
    virtual void SetAng_Roll_deg(double Ang_Roll_deg) override;
    virtual void SetAng_Pitch_deg(double Ang_Pitch_deg) override;
    virtual void SetAng_Yaw_deg(double Ang_Yaw_deg) override;
    virtual const Vector3D & GetPosition_m() const override;
    virtual void SetPosition_m(const Vector3D &rPos) override;
    virtual void SetName(const char* sName) override;
    virtual const std::string & GetName() const override;
    void SetScale(const Vector3D & scale) {_Scale = scale;}
    void SetShift(const Vector3D & shift) {_Shift = shift;}
    void SetRGB(const Vector3D & rgb) {_RGB = rgb;}
    const Vector3D & GetScale() const {return _Scale;}
    const Vector3D & GetShift() const {return _Shift;}
    const Vector3D & GetRGB() const {return _RGB;}  
};
#endif