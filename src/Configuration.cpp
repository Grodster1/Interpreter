#include "Configuration.hh"
#include <string>
#include <list>

Configuration::Configuration(){}

void Configuration::SetPluginsPath(const std::list<std::string>& Paths){
    _PluginPaths = Paths;
}
const std::list<std::string> Configuration::GetPluginPaths(){
    return _PluginPaths;
}