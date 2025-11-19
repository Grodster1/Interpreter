#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include "Scene.hh"
#include "Set4LibInterfaces.hh"

class ProgramInterpreter{
private:
    Scene _Scn;
    Set4LibInterfaces _LibManager; 

public:
    ProgramInterpreter();
    ~ProgramInterpreter();
    bool ExecProgram(const char* sFileName); 
    bool Read_XML_Config(const char* sFileName);
};


#endif