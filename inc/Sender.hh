#ifndef SENDER_HH
#define SENDER_HH

#include "Scene.hh"
#include "ComChannel.hh"

class Sender{
private:
    volatile bool _ContinueLooping = true;
    Scene* _pScene = nullptr;
    ComChannel* _pComChannel = nullptr;


public:
    Sender(Scene *pScene, ComChannel *pComChannel);
    bool ShouldContinueLooping() const { return _ContinueLooping; };
    bool CancelContinueLooping() {_ContinueLooping = false;};
    void Watching_and_Sending();
};

#endif 