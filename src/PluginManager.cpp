#include <iostream>
#include <PluginManager.hh>

PluginManager::PluginManager(std::list<std::string> libPaths){
    for(std::string& path : libPaths){
        try{
            std::shared_ptr<LibInterface> pLib = std::make_shared<LibInterface>(path);
            std::string cmdName = pLib->GetCmdName();
            _libMap[cmdName] = pLib;

            std::cout << "Poprawnie załadowano wtyczkę dla komendy " << cmdName << std::endl;
        }
        catch(const std::runtime_error &error){
            std::cerr << "Wystapil blad przy ladowaniu wtyczki z pliku: " << path << "\nError: " << error.what() << std::endl;
        }
    }
}