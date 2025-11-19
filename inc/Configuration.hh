#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "Scene.hh"
#include "Set4LibInterfaces.hh"

class Configuration{
private:
    std::list<std::string> _PluginPaths;

public:
    Configuration();
    ~Configuration();
    void SetPluginsPath(const std::list<std::string>& Paths);
    const std::list<std::string> GetPluginPaths(); 
};


#endif