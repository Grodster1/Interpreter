#ifndef SCENE_HH
#define SCENE_HH

#include "AbstractScene.hh"
#include "AbstractMobileObj.hh"
#include "AccessControl.hh"
#include <map>
#include <memory>



class Scene: public AbstractScene, public AccessControl{
private:
    std::map<std::string, std::shared_ptr<AbstractMobileObj>> _Set_MobileObjs;

public:
    Scene() {};
    ~Scene() {};
    virtual AbstractMobileObj* FindMobileObj(const char *sName) override;
    virtual void AddMobileObj(AbstractMobileObj *pMobObj) override;

    //DODANE DLA ETAPU 3
    virtual void LockAccess() override { AccessControl::LockAccess(); }
    virtual void UnlockAccess() override { AccessControl::UnlockAccess(); }
    virtual void MarkChange() override { AccessControl::MarkChange(); }
    const std::map<std::string, std::shared_ptr<AbstractMobileObj>>& GetMobileObjs() const {
        return _Set_MobileObjs;
    }
};  


#endif