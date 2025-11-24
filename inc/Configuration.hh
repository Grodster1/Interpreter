#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include "Cuboid.hh"

class Configuration{
private:
    std::list<std::string> _PluginPaths;
    Scene _Scene;

public:
    Configuration() {};
    ~Configuration() {};
    void SetPluginsPath(const std::list<std::string>& Paths);
    const std::list<std::string> GetPluginPaths(); 
    Scene& GetSceneReference();
};


#endif