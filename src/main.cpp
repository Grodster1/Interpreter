#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <list>
#include <sstream>
#include <cstdlib>
#include <string>
#include <array>
#include "ProgramInterpreter.hh"

using namespace std;

int main()
{
  std::setlocale(LC_ALL, "C"); 
  std::locale::global(std::locale("C"));

  ProgramInterpreter Interp;
  Interp.Read_XML_Config("../config/config.xml");
  Interp.ExecProgram("./cmd.tmp");
}
