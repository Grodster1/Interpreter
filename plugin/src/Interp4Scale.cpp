#include <iostream>
#include <unistd.h>
#include "Interp4Scale.hh"
#include "Cuboid.hh"

extern "C"{
    AbstractInterp4Command* CreateCmd(void);
    const char* GetCmdName() {return "Scale";}
}

AbstractInterp4Command* CreateCmd(void) { return Interp4Scale::CreateCmd(); }

Interp4Scale::Interp4Scale(): _ObjName(""){
    _Scale[0]=1;
    _Scale[1]=1;
    _Scale[2]=1;
}

void Interp4Scale::PrintCmd() const {
  std::cout << GetCmdName() << " " << _ObjName << " " << _Scale[0] << " " << _Scale[1] << " " << _Scale[2] << std::endl;
}

const char* Interp4Scale::GetCmdName() const { return ::GetCmdName(); }

bool Interp4Scale::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) {
  
  AbstractMobileObj* pObj = rScn.FindMobileObj(_ObjName.c_str());
  
  if (!pObj) {
    std::cerr << "Blad: Nie znaleziono obiektu: " << _ObjName << std::endl;
    return false;
  }

  Cuboid* pCube = dynamic_cast<Cuboid*>(pObj);
  if (!pCube) {
    std::cerr << "Blad: Obiekt " << _ObjName << " nie jest typu Cuboid!" << std::endl;
    return false;
  }

  rScn.LockAccess();
  pCube->SetScale(_Scale); 
  rScn.MarkChange();       
  rScn.UnlockAccess();
  
  return true;
}

bool Interp4Scale::ReadParams(std::istream& Strm_CmdsList) {
  Strm_CmdsList >> _ObjName >> _Scale[0] >> _Scale[1] >> _Scale[2];
  return !Strm_CmdsList.fail();
}

AbstractInterp4Command* Interp4Scale::CreateCmd() { return new Interp4Scale(); }

void Interp4Scale::PrintSyntax() const {
  std::cout << "Scale  NazwaObiektu  ScaleX  ScaleY  ScaleZ" << std::endl;
}