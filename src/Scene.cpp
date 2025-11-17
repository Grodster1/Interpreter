#include "Scene.hh"
#include <iostream>

AbstractMobileObj* Scene::FindMobileObj(const char *sName){
    auto it = _Set_MobileObjs.find(sName);
    if(it == _Set_MobileObjs.end()){
        return nullptr;
    }
    return it->second.get();
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj){
    try{
        std::string _pObjName = pMobObj->GetName();
        std::shared_ptr<AbstractMobileObj> _pObj(pMobObj);
        _Set_MobileObjs[_pObjName] = _pObj;
        std::cout << "Poprawnie zaladowano obiekt: " << _pObjName << std::endl;
    }
    catch(const std::runtime_error &error){
        std::cerr<<"Wystapil blad przy ladowaniu obiektu. Error: " << error.what() << std::endl;
    }
}