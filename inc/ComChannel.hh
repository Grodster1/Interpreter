#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

#include "AbstractComChannel.hh"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <mutex>
class ComChannel : public AbstractComChannel{

private:
    int _Socket = 0;
    std::mutex _Mutex;

public:
    ComChannel();

    virtual void Init(int Socket) override {_Socket = Socket;};
    virtual int GetSocket() const override {return _Socket;};
    virtual void LockAccess() override {_Mutex.lock();};
    virtual void UnlockAccess() override {_Mutex.unlock();};
    virtual std::mutex &UseGuard() override;

    int Send(const char* sMsg);
};

#endif