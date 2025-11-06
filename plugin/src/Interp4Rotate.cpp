#include <iostream>
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
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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
