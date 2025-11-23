#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH


#include <string>
#include "AbstractInterp4Command.hh"

class LibInterface{
    void* _libHandle;
    std::string _cmdName;
    AbstractInterp4Command* (*_pCreateCmd)(void); //_pCreateCmd wskazuje na funkcję z .so, która tworzy i zwraca obiekt pasujący do interfejsu AbstractInterp4Command
    const char* (*_pGetCmd)(void);
    
public:
    LibInterface(const std::string& libPath);
    ~LibInterface();
    const std::string& GetCmdName() const {return _cmdName;} 
    AbstractInterp4Command* CreateCmd() {return _pCreateCmd();}
};

#endif