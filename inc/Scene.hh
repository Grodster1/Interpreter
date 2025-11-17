#ifndef SCENE_HH
#define SCENE_HH

#include "AbstractScene.hh"
#include "AbstractMobileObj.hh"
#include <map>
#include <memory>



class Scene: public AbstractScene{
private:
    std::map<std::string, std::shared_ptr<AbstractMobileObj>> _Set_MobileObjs;

public:
    Scene() {};
    ~Scene() {};
    virtual AbstractMobileObj* FindMobileObj(const char *sName);
    virtual void AddMobileObj(AbstractMobileObj *pMobObj);
};


#endif