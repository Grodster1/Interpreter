#include "ComChannel.hh"
#include <iostream>

int ComChannel::Send(const char* sMsg){
    //LockAccess();

    std::lock_guard<std::mutex> lock(_Mutex); //Przy zniszczonym obiekcie destruktor wywołuje unlock()

    ssize_t IlWyslanych;
    ssize_t IlDoWyslania = (ssize_t) strlen(sMsg);

    while((IlWyslanych = write(_Socket, sMsg, IlDoWyslania)) > 0){
        IlDoWyslania -= IlWyslanych;
        sMsg += IlWyslanych; //Przesunięcie wskaznika 
    }
    if(IlWyslanych < 0){
        std::cerr << "*** Blad przesylania napisu" << std::endl;
    }
    //UnlockAccess();
    return 0;
}