#include "ProgramInterpreter.hh"
#include "Cuboid.hh"    
#include <string>
#include <sstream>
#include <array>
#include <unistd.h>     
#include <map>          

// Port serwera graficznego
#define PORT 6217
ProgramInterpreter::ProgramInterpreter(){}


/*!
 * Metoda wywołana do obsługi pliku XML. Wykorzystuje funkcje z xmlinterp.
 * Ładowanie wtyczek odczytanych z pliku XML.
 * \param[in] sFileName - nazwa pliku konfiguracyjnego XML.
 */
bool ProgramInterpreter::Read_XML_Config(const char* sFileName){
    if(!ReadFile(sFileName, _Config)){
        std::cerr << "Blad przy wywolaniu funkcji ReadFile(sFileName, _Config)" << std::endl;
        return false;
    }

    std::list<std::string> pluginPaths = _Config.GetPluginPaths();
    if(!_LibManager.LoadPlugins(pluginPaths)){
        std::cerr << "Blad przy ladowaniu bibliotek dynamicznych" << std::endl;
        return false;
    }
    std::cout << "Pomyslnie sparsowano i wczytano biblioteki dynamiczne" << std::endl;
    return true;

}

/*!
 * Metoda odpowiedzialna za uruchomienie parsera pliku z instrukcjami dla obiektów.
 * Wydobycie z pliku keyWord charakterystycznych dla konkretnych wtyczek i wyświetlenie ich składni.
 * \param[in] sFileName - nazwa pliku z instrukcjami dla obiektu.
 */
// bool ProgramInterpreter::ExecProgram(const char* sFileName){
//     std::string cmd = "cpp " + std::string(sFileName); 
//     FILE* File = popen(cmd.c_str(), "r");
//     std::stringstream ppStream;
//     std::array<char, 128> buf;
//     std::string keyWord;


//     if(!File){
//         std::cerr << "Blad przy wywolaniu funkcji popen()" << std::endl;
//     return false;
//     }

//     while(fgets(buf.data(), buf.size(), File)){
//         ppStream << buf.data();
//     }
//     pclose(File);

//     while(ppStream >> keyWord){
//         if(_LibManager.isInMap(keyWord)){
//             AbstractInterp4Command* pCmd = _LibManager.CreateCmd(keyWord);
//             if(pCmd){
//                 pCmd->PrintSyntax();
//                 pCmd->ReadParams(ppStream);
//                 pCmd->PrintCmd();
//             }
//             delete pCmd;
//         }
//     }
//     return true;
// }

bool ProgramInterpreter::ExecProgram(const char* sFileName){
    
    
    if (!_ComChannel.OpenConnection(PORT)) { 
        std::cerr << "Blad: Nie udalo sie polaczyc z serwerem graficznym na porcie " << PORT << "!" << std::endl;
        return false;
    }
    std::cout << "Polaczono z serwerem graficznym." << std::endl;

    _ComChannel.LockAccess();
    _ComChannel.Send("Clear\n");
    _ComChannel.UnlockAccess();

    std::cout << "Wysylanie definicji obiektow do serwera..." << std::endl;

    Scene& rScn = _Config.GetSceneReference();
    
    const std::map<std::string, std::shared_ptr<AbstractMobileObj>> &objects = rScn.GetMobileObjs();
    
    std::map<std::string, std::shared_ptr<AbstractMobileObj>>::const_iterator it;

    for (it = objects.begin(); it != objects.end(); ++it) {
        std::shared_ptr<AbstractMobileObj> pObj = it->second;

        std::shared_ptr<Cuboid> pCube = std::dynamic_pointer_cast<Cuboid>(pObj); 

        if (pCube) {
            std::stringstream ss;
            
            auto formatVec = [](const Vector3D& v) -> std::string {
                std::stringstream s;
                s << "(" << v[0] << "," << v[1] << "," << v[2] << ")";
                return s.str();
            };

            ss << "AddObj";
            ss << " Name=" << pCube->GetName();
            ss << " RGB=" << formatVec(pCube->GetRGB());
            ss << " Scale=" << formatVec(pCube->GetScale());
            ss << " Shift=" << formatVec(pCube->GetShift());
            ss << " RotXYZ_deg=" << formatVec(pCube->GetRPY());
            ss << " Trans_m=" << formatVec(pCube->GetPosition_m());
            ss << "\n";

            _ComChannel.LockAccess();
            _ComChannel.Send(ss.str().c_str());
            _ComChannel.UnlockAccess();
        }
    }

    // ========================================================================
    // KROK 3: Uruchomienie wątku komunikacyjnego (Sender)
    // ========================================================================
    std::cout << "Uruchamianie watku aktualizujacego stan (Sender)..." << std::endl;
    
    Sender sender(&rScn, &_ComChannel);
    // Uruchamiamy metodę w nowym wątku
    std::thread senderThread(&Sender::Watching_and_Sending, &sender);


    // ========================================================================
    // KROK 4: Przetwarzanie komend z pliku (Główna pętla)
    // ========================================================================
    std::string cmd = "cpp -P " + std::string(sFileName); 
    FILE* File = popen(cmd.c_str(), "r");
    std::stringstream ppStream;
    std::array<char, 128> buf;
    std::string keyWord;

    if(!File){
        std::cerr << "Blad przy wywolaniu funkcji popen()" << std::endl;
        sender.CancelContinueLooping();
        senderThread.join();
        return false;
    }

    while(fgets(buf.data(), buf.size(), File)){
        ppStream << buf.data();
    }
    pclose(File);

    while(ppStream >> keyWord){
        if(_LibManager.isInMap(keyWord)){
            AbstractInterp4Command* pCmd = _LibManager.CreateCmd(keyWord);
            if(pCmd){
                if(pCmd->ReadParams(ppStream)){
                    
                    std::cout << "Wykonywanie komendy: ";
                    pCmd->PrintCmd(); 

                    
                    if (!pCmd->ExecCmd(rScn, "", _ComChannel)) {
                         std::cerr << "Blad wykonania komendy!" << std::endl;
                    }
                } else {
                    std::cerr << "Blad wczytywania parametrow komendy!" << std::endl;
                }
            }
            delete pCmd;
        }
    }

    // ========================================================================
    // KROK 5: Zakończenie pracy
    // ========================================================================
    std::cout << "Koniec programu. Zamykanie..." << std::endl;

    sender.CancelContinueLooping(); 
    senderThread.join();             

    _ComChannel.LockAccess();
    _ComChannel.Send("Close\n");
    _ComChannel.UnlockAccess();
    
    
    return true;
}