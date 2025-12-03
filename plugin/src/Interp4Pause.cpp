#include <iostream>
#include "Interp4Pause.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 *
 */
Interp4Pause::Interp4Pause(): _PauseTime(0) 
{}


/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _PauseTime << endl;
}


/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Pause::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  //IMPLEMENTACJA OBSLUGI PRZEMIESZCZENIA
  rScn.MarkChange();
  return true;
}


/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> _PauseTime)){
    std::cout << "Nie wczytano poprawnie czasu pauzy symulacji" << std::endl;
    return false;
  }
  return true;
}

/*!
 *
 */
AbstractInterp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "Pause  CzasPauzy" << endl;
}
