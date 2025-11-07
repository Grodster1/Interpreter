#include <map>
#include <list>
#include <memory>
#include <string>
#include "AbstractInterp4Command.hh"
#include "LibInterface.hh"

class PluginManager{
    std::map<std::string, std::shared_ptr<LibInterface>> _libMap;

public:
    PluginManager(std::list<std::string> libPaths);
    ~PluginManager();

};