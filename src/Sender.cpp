#include "Sender.hh"
#include <iostream>
#include <sstream>
#include <unistd.h> 

using namespace std;

Sender::Sender(Scene *pScene, ComChannel *pComChannel) 
    : _pScene(pScene), _pComChannel(pComChannel)
{
}

/*!
 * \brief Główna pętla wątku komunikacyjnego.
 * Śledzi zmiany na scenie i wysyła je do serwera.
 */
void Sender::Watching_and_Sending()
{
    while (ShouldContinueLooping()) {
        _pScene->LockAccess();

        if (_pScene->IsChanged()) {
            _pScene->CancelChange();
            std::stringstream ss;

            const std::map<std::string, std::shared_ptr<AbstractMobileObj>> &objects = _pScene->GetMobileObjs();

            std::map<std::string, std::shared_ptr<AbstractMobileObj>>::const_iterator it;

            for (it = objects.begin(); it != objects.end(); ++it) {
                ss << it->second->GetStateDesc();
            }

            _pScene->UnlockAccess();
            _pComChannel->Send(ss.str().c_str());

        } else {
            _pScene->UnlockAccess();
        }
        usleep(10000);
    }
}