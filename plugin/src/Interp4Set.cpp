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
Interp4Set::Interp4Set(): obj_name("Jajco"),pos_x_(0), pos_y_(0), pos_z_(0), angle_x_(0), angle_y_(0), angle_z_(0) 
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << obj_name << " " <<  pos_x_ << " " <<  pos_y_ << " " << pos_z_ << " " << angle_x_ << " " << angle_y_ << " " << angle_z_<< endl;
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
  if(!(Strm_CmdsList >> obj_name)){
    std::cout << "Nie wczytano poprawnie nazwy obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> pos_x_)){
    std::cout << "Nie wczytano poprawnie pozycji x obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> pos_y_)){
    std::cout << "Nie wczytano poprawnie pozycji y obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> pos_z_)){
    std::cout << "Nie wczytano poprawnie pozycji z obiektu" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> angle_x_)){
    std::cout << "Nie wczytano poprawnie orientacji wzgledem osi x" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> angle_y_)){
    std::cout << "Nie wczytano poprawnie orientacji wzgledem osi y" << std::endl;
    return false;
  }
  if(!(Strm_CmdsList >> angle_z_)){
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
  cout << "Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
