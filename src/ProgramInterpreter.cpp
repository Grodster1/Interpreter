#include "ProgramInterpreter.hh"
#include <string>
#include <sstream>
#include <array>

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
bool ProgramInterpreter::ExecProgram(const char* sFileName){
    std::string cmd = "cpp " + std::string(sFileName); 
    FILE* File = popen(cmd.c_str(), "r");
    std::stringstream ppStream;
    std::array<char, 128> buf;
    std::string keyWord;


    if(!File){
        std::cerr << "Blad przy wywolaniu funkcji popen()" << std::endl;
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
                pCmd->PrintSyntax();
                pCmd->ReadParams(ppStream);
                pCmd->PrintCmd();
            }
            delete pCmd;
        }
    }
    return true;
}