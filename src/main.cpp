#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <list>
#include <sstream>
#include <cstdlib>
#include <array>
#include "AbstractInterp4Command.hh"
#include "Set4LibInterfaces.hh"

using namespace std;

#define PLUGIN_NAME__rotate "libInterp4Rotate.so"


int main()
{
  /*void *pLibHnd_Rotate = dlopen(PLUGIN_NAME__rotate,RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Rotate)(void);
  void *pFun;

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: " PLUGIN_NAME__rotate << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);


  AbstractInterp4Command *pCmd = pCreateCmd_Rotate();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Rotate);*/
  std::string cmdFile = "./cmd.tmp";
  std::list<std::string> pluginList = {"libInterp4Rotate.so", "libInterp4Set.so", "libInterp4Move.so", "libInterp4Pause.so"};
  std::string keyWord;
  Set4LibInterfaces pManager;

  std::string cmd = "cpp " + cmdFile;
  std::stringstream ppStream;
  std::array<char, 128> buf;

  FILE* File = popen(cmd.c_str(), "r");
  if(!File){
    std::cerr << "Blad przy wywolaniu funkcji popen()" << std::endl;
    return 1;
  }

  while (fgets(buf.data(), buf.size(), File)){
    ppStream << buf.data();
  }
  pclose(File);

  pManager.LoadPlugins(pluginList);

  std::cout << ppStream.str() << std::endl;
  while(ppStream >> keyWord){
    if(pManager.isInMap(keyWord)){
      AbstractInterp4Command* pCmd = pManager.CreateCmd(keyWord);
      if(pCmd){
        pCmd->PrintSyntax();
      }
      delete pCmd;
    }
  }
}
