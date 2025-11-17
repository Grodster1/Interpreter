#include <iostream>
#include "PluginManager.hh"

PluginManager::PluginManager(std::list<std::string> libPaths){
    for(std::string& path : libPaths){
        try{
            std::shared_ptr<LibInterface> pLib = std::make_shared<LibInterface>(path);
            std::string cmdName = pLib->GetCmdName();
            _libMap[cmdName] = pLib;

            std::cout << "Poprawnie zaladowano wtyczke dla komendy " << cmdName << std::endl;
        }
        catch(const std::runtime_error &error){
            std::cerr << "Wystapil blad przy ladowaniu wtyczki z pliku: " << path << "\nError: " << error.what() << std::endl;
        }
    }
}

bool PluginManager::isInMap(const std::string& cmdName) const{
    if(auto it = _libMap.find(cmdName) == _libMap.end()){
        return false;
    }
    return true;
}

AbstractInterp4Command* PluginManager::CreateCmd(const std::string& cmdName){
    auto it = _libMap.find(cmdName);
    if(it == _libMap.end()){
        return nullptr;
    }
    std::shared_ptr ptr = it->second;
    return ptr->CreateCmd();
}

/*AbstractInterp4Command* PluginManager::ReadParams(const std::istream& Strm_CmdsList, const std::string& cmdName){
    auto it = _libMap.find(cmdName);
    if(it == _libMap.end()){
        return nullptr;
    }
    std::shared_ptr ptr = it->second;
    return ptr->ReadParams();
}*/

PluginManager::~PluginManager(){}