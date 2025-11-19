#include <iostream>
#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces(){};

bool Set4LibInterfaces::LoadPlugins(const std::list<std::string> & libPaths){
    bool allPluginsLoaded = true;
    
    for(std::string path : libPaths){
        try{
            std::shared_ptr<LibInterface> pLib = std::make_shared<LibInterface>(path);
            std::string cmdName = pLib->GetCmdName();
            _libMap[cmdName] = pLib;
            
            std::cout << "Poprawnie zaladowano wtyczke dla komendy " << cmdName << std::endl;
            
        }
        catch(const std::runtime_error &error){
            std::cerr << "Wystapil blad przy ladowaniu wtyczki z pliku: " << path << "\nError: " << error.what() << std::endl;
            allPluginsLoaded=false;
        }
    }
    return allPluginsLoaded;
}

bool Set4LibInterfaces::isInMap(const std::string& cmdName) const{
    auto it = _libMap.find(cmdName);
    if(it == _libMap.end()){
        return false;
    }
    return true;
}

AbstractInterp4Command* Set4LibInterfaces::CreateCmd(const std::string& cmdName){
    auto it = _libMap.find(cmdName);
    if(it == _libMap.end()){
        return nullptr;
    }
    std::shared_ptr ptr = it->second;
    return ptr->CreateCmd();
}

Set4LibInterfaces::~Set4LibInterfaces(){}