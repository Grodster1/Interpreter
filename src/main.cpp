#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <list>
#include <sstream>
#include <cstdlib>
#include <string>
#include <array>
#include "AbstractInterp4Command.hh"
#include "Set4LibInterfaces.hh"

using namespace std;

int main()
{
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

  //std::cout << ppStream.str() << std::endl;
  while(ppStream >> keyWord){
    if(pManager.isInMap(keyWord)){
      AbstractInterp4Command* pCmd = pManager.CreateCmd(keyWord);
      if(pCmd){
        pCmd->PrintSyntax();
        pCmd->ReadParams(ppStream);
        pCmd->PrintCmd();
      }
      delete pCmd;
    }
  }
}
