#include <map>
#include <list>
#include <memory>
#include <string>
#include "AbstractInterp4Command.hh"
#include "LibInterface.hh"

class Set4LibInterfaces{
    std::map<std::string, std::shared_ptr<LibInterface>> _libMap;

public:
    Set4LibInterfaces();
    ~Set4LibInterfaces();
    bool LoadPlugins(const std::list<std::string> & libPaths);
    bool isInMap(const std::string& cmdName) const;
    AbstractInterp4Command* CreateCmd(const std::string& cmdName);

};