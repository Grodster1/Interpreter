#include <iostream>
#include "Interp4Color.hh"
#include "Cuboid.hh" 


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Color"; }
}

AbstractInterp4Command* CreateCmd(void) { return Interp4Color::CreateCmd(); }

Interp4Color::Interp4Color(): _ObjName(""){
    _RGB[0]=255;
    _RGB[1]=255;
    _RGB[2]=255;
}

void Interp4Color::PrintCmd() const {
  std::cout << GetCmdName() << " " << _ObjName << " " << _RGB[0] << " " << _RGB[1] << " " << _RGB[2] << std::endl;
}

const char* Interp4Color::GetCmdName() const { return ::GetCmdName(); }

bool Interp4Color::ExecCmd(AbstractScene &rScn, const char *sMobObjName, AbstractComChannel &rComChann) {
  
  AbstractMobileObj* pObj = rScn.FindMobileObj(_ObjName.c_str());
  
  if (!pObj) {
    std::cerr << "Blad: Nie znaleziono obiektu: " << _ObjName << std::endl;
    return false;
  }

  Cuboid* pCube = dynamic_cast<Cuboid*>(pObj);
  if (!pCube) {
    std::cerr << "Blad: Obiekt " << _ObjName << " nie obsluguje koloru!" << std::endl;
    return false;
  }

  rScn.LockAccess();
  pCube->SetRGB(_RGB);
  rScn.MarkChange();   
  rScn.UnlockAccess();
  
  return true;
}

bool Interp4Color::ReadParams(std::istream& Strm_CmdsList) {
  Strm_CmdsList >> _ObjName >> _RGB[0] >> _RGB[1] >> _RGB[2];
  return !Strm_CmdsList.fail();
}

AbstractInterp4Command* Interp4Color::CreateCmd() { return new Interp4Color(); }

void Interp4Color::PrintSyntax() const {
  std::cout << "Color  NazwaObiektu  R  G  B" << std::endl;
}