#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include <iostream>
#include <list>
#include <memory>
#include <thread>
#include <atomic>

#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include "Configuration.hh"
#include "xmlinterp.hh"
#include "ComChannel.hh" 
#include "Sender.hh"

class ProgramInterpreter{
private:
    Scene _Scn;
    Set4LibInterfaces _LibManager;
    Configuration _Config;
    ComChannel _ComChannel;
    int _Socket;

public:
    ProgramInterpreter();
    ~ProgramInterpreter() {};
    bool ExecProgram(const char* sFileName); 
    bool Read_XML_Config(const char* sFileName);
};


#endif