#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "LibInterface.hh"

LibInterface::LibInterface(const std::string& libPath) : _libHandle(nullptr), _pCreateCmd(nullptr), _pGetCmd(nullptr){
    _libHandle = dlopen(libPath.c_str(), RTLD_LAZY);
    if(!_libHandle){
        throw std::runtime_error(std::string("Blad dlopen: ") + dlerror());
        //std::cerr << "!!! Blad: " << dlerror() << std::endl;
    }

    

    void* pFun = dlsym(_libHandle, "CreateCmd");
    if(!pFun){
        throw std::runtime_error(std::string("Blad dlsym (CreateCmd): ") + dlerror());
        //std::cerr << "!!! Nie znaleziono funkcji CreateCmd: " << dlerror() << std::endl; 
    }

    _pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
    
    void* pFunName = dlsym(_libHandle, "GetCmdName");
    if(!pFunName){
        //std::cerr << "!!! Nie znalezniono funkcji GetCmdName: " << dlerror() << std::endl;
        throw std::runtime_error(std::string("Blad dlsym (GetCmdName): ") + dlerror());
    }


    _pGetCmd = reinterpret_cast<const char* (*)(void)>(pFunName);
    _cmdName = _pGetCmd();
}

LibInterface::~LibInterface(){
    if(_libHandle){
        dlclose(_libHandle);
    }
}