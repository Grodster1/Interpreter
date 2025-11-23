#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include "Configuration.hh"
#include "xmlinterp.hh"

class ProgramInterpreter{
private:
    Scene _Scn;
    Set4LibInterfaces _LibManager;
    Configuration _Config;


public:
    ProgramInterpreter();
    ~ProgramInterpreter() {};
    bool ExecProgram(const char* sFileName); 
    bool Read_XML_Config(const char* sFileName);
};


#endif