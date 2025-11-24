#include "Configuration.hh"
#include <string>
#include <list>

void Configuration::SetPluginsPath(const std::list<std::string>& Paths){
    _PluginPaths = Paths;
}
const std::list<std::string> Configuration::GetPluginPaths(){
    return _PluginPaths;
}

Scene& Configuration::GetSceneReference(){
    return _Scene;
}