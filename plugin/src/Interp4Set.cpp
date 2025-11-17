#include <iostream>
#include "Interp4Set.hh"

using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _ObjName("Jajco"),_PosX(0), _PosY(0), _PosZ(0), _AngleX(0), _AngleY(0), _AngleZ(0) 
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ObjName << " " <<  _PosX << " " <<  _PosY << " " << _PosZ << " " << _AngleX << " " << _AngleY << " " << _AngleZ<< endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( AbstractScene      &rScn, 
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
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> _ObjName)){
    std::cout << "Nie wczytano poprawnie nazwy obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _PosX)){
    std::cout << "Nie wczytano poprawnie pozycji x obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _PosY)){
    std::cout << "Nie wczytano poprawnie pozycji y obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _PosZ)){
    std::cout << "Nie wczytano poprawnie pozycji z obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _AngleX)){
    std::cout << "Nie wczytano poprawnie orientacji wzgledem osi x" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _AngleY)){
    std::cout << "Nie wczytano poprawnie orientacji wzgledem osi y" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> _AngleZ)){
    std::cout << "Nie wczytano poprawnie orientacji wzgledem osi z" << std::endl;
    return false;
  }
  return true;
}

/*!
 *
 */
AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "Set  NazwaObiektu  wsp_x  wsp_y  wsp_z  kat_OX  kat_OY  kat_OZ" << endl;
}
