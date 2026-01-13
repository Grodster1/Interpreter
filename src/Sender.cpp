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

            // 1. Pobieramy referencję do mapy (bez auto!)
            const std::map<std::string, std::shared_ptr<AbstractMobileObj>> &objects = _pScene->GetMobileObjs();

            // 2. Deklarujemy iterator (bez auto!)
            std::map<std::string, std::shared_ptr<AbstractMobileObj>>::const_iterator it;

            // 3. Pętla for z iteratorem
            for (it = objects.begin(); it != objects.end(); ++it) {
                // it->first to klucz (string), it->second to wartość (shared_ptr)
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