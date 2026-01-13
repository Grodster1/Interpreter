#include <iostream>
#include <unistd.h>
#include <cmath>
#include "Interp4Rotate.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _ObjName("Jajco"), _AxisName("OX"), _RotSpeed(0), _RotDegree(0) 
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ObjName << " " << _AxisName <<  " " << _RotSpeed  << " " << _RotDegree << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  //IMPLEMENTACJA OBSLUGI PRZEMIESZCZENIA
  AbstractMobileObj* pObj = rScn.FindMobileObj(this->_ObjName.c_str());
  if (pObj == nullptr) {
    std::cerr << "Blad: Nie znaleziono obiektu: " << this->_ObjName << std::endl;
    return false;
  }

  // if (_RotSpeed <= 0) {
  //     std::cerr << "Blad: Predkosc obrotu musi byc dodatnia!" << std::endl;
  //     return false;
  // }

  const double time_step_s = 0.02; 
  const int time_step_us = 20000;

  double total_time_s = std::abs(_RotDegree / _RotSpeed);
  int animation_steps = (int)ceil(total_time_s / time_step_s);
  
  if (animation_steps < 1) animation_steps = 1;

  double step_angle = _RotDegree / animation_steps;

  int axis_idx = -1;
  if(_AxisName=="OX") axis_idx=0;
  else if(_AxisName=="OY") axis_idx=1;
  else if(_AxisName=="OZ") axis_idx=2;
  else{
    std::cerr << "Blad: Nieznana nazwa osi: " << _AxisName << "(Dostepne: OX OY OZ)" << std::endl;
    return false;
  }



  for(int i = 0; i<animation_steps; ++i){
    rScn.LockAccess();
    Vector3D rpy = pObj->GetRPY();
    rpy[axis_idx] += step_angle;
    pObj->SetRPY(rpy);

    rScn.MarkChange();
    rScn.UnlockAccess();
    usleep(time_step_us);
  }
  
  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> _ObjName)){
    std::cout << "Nie wczytano poprawnie nazwy obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _AxisName)){
    std::cout << "Nie wczytano poprawnie nazwy osi obrotu obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _RotSpeed)){
    std::cout << "Nie wczytano poprawnie predkosci obrotu obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _RotDegree)){
    std::cout << "Nie wczytano poprawnie zakresu obrotu obiektu" << std::endl;
    return false;
  }
  return true;
}

/*!
 *
 */
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "Rotate  NazwaObiektu  NazwaOsi  SzybkoscKatowa [deg/s]  KatObrotu [deg]" << endl;
}
