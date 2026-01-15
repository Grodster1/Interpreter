#include "ComChannel.hh"
#include <iostream>

using namespace std;

ComChannel::ComChannel() {}

ComChannel::~ComChannel() {
    if (_Socket > 0) {
        close(_Socket);
    }
}


bool ComChannel::OpenConnection(int Port) {
    struct sockaddr_in DaneAdSerw;

    bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));
    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(Port);

    _Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_Socket < 0) {
        cerr << "*** Blad otwarcia gniazda." << endl;
        return false;
    }

    if (connect(_Socket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0) {
        cerr << "*** Brak mozliwosci polaczenia do portu: " << Port << endl;
        return false;
    }

    return true; 
}


int ComChannel::Send(const char* sMsg) {

    ssize_t IlWyslanych;
    ssize_t IlDoWyslania = (ssize_t) strlen(sMsg);

    if (_Socket <= 0) {
        std::cerr << "*** Blad: Proba wyslania przez nieaktywne gniazdo!" << std::endl;
        return -1;
    }

    while ((IlWyslanych = write(_Socket, sMsg, IlDoWyslania)) > 0) {
        IlDoWyslania -= IlWyslanych;
        sMsg += IlWyslanych;
    }
    if (IlWyslanych < 0) {
        std::cerr << "*** Blad przesylania napisu" << std::endl;
    }
    return 0;
}