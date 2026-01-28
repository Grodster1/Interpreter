#include <iostream>
#include <unistd.h>
#include <cmath>
#include "Interp4Move.hh"



using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _ObjName("Jajco"),_Speed_mmS(0), _Distance(0) 
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ObjName << " " <<  _Speed_mmS  << " " << _Distance << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  AbstractMobileObj* pObj = rScn.FindMobileObj(this->_ObjName.c_str()); 
  if (pObj == nullptr) {
    std::cerr << "Blad: Nie znaleziono obiektu: " << this->_ObjName << std::endl;
    return false;
  }

  if (_Speed_mmS == 0) {
      std::cerr << "Blad: Predkosc nie moze byc 0!" << std::endl;
      return false; 
  }

  const double time_step_s = 0.02; 
  const int time_step_us = 20000;

  double total_time_s = std::abs(_Distance / _Speed_mmS);
  
  int animation_steps = (int)ceil(total_time_s / time_step_s);
  if (animation_steps < 1) animation_steps = 1;

  double step_distance_m = (_Speed_mmS * time_step_s); 
  
  double delta_per_step = _Distance / animation_steps;
  

  int direction = (_Speed_mmS < 0) ? -1 : 1;
  delta_per_step *= direction; 

  for(int i = 0; i < animation_steps; ++i){
    rScn.LockAccess(); 
    Vector3D pos = pObj->GetPosition_m();
    Vector3D rpy = pObj->GetRPY(); 

    double pitch_rad = rpy[1] * M_PI / 180.0;
    double yaw_rad   = rpy[2] * M_PI / 180.0;

    double dx = delta_per_step * cos(pitch_rad) * cos(yaw_rad);
    double dy = delta_per_step * cos(pitch_rad) * sin(yaw_rad);
    double dz = delta_per_step * sin(pitch_rad);

    pos[0] += dx;
    pos[1] += dy;
    pos[2] += dz;

    pObj->SetPosition_m(pos);
    rScn.MarkChange();
    rScn.UnlockAccess();
    
    usleep(time_step_us);
  }
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> _ObjName)){
    std::cout << "Nie wczytano poprawnie nazwy obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _Speed_mmS)){
    std::cout << "Nie wczytano poprawnie predkosci obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _Distance)){
    std::cout << "Nie wczytano poprawnie dystansu ruchu" << std::endl;
    return false;
  }
  return true;
}

/*!
 *
 */
AbstractInterp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
