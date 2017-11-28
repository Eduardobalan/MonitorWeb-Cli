//
// Created by eduardo on 13/10/17.
//

#include <cstring>
#include <zconf.h>
#include "SystemLog.h"
#include "ConfigFile/ConfigFile.h"
#include "SystemData.h"

bool SystemLog::ativarEmTelaInfo;
bool SystemLog::ativarEmTelaWarming;
bool SystemLog::ativarEmTelaErro;
bool SystemLog::ativarEmArquivoInfo;
bool SystemLog::ativarEmArquivoWarming;
bool SystemLog::ativarEmArquivoErro;



void SystemLog::lerLogConf(){
    try {
        chdir("/home/eduardo/Workspace/TCC-monitorWeb-Cliente");
        ConfigFile configFile("ConfigLog.conf", ":");
        configFile.load();

        SystemLog::ativarEmTelaInfo = configFile.getBool("ativarEmTelaInfo");
        SystemLog::ativarEmTelaWarming = configFile.getBool("ativarEmTelaWarming");
        SystemLog::ativarEmTelaErro = configFile.getBool("ativarEmTelaErro");

        SystemLog::ativarEmArquivoInfo = configFile.getBool("ativarEmArquivoInfo");
        SystemLog::ativarEmArquivoWarming = configFile.getBool("ativarEmArquivoWarming");
        SystemLog::ativarEmArquivoErro = configFile.getBool("ativarEmArquivoErro");


    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void SystemLog::execLog(char tipo, const string &log){
    //log em tela;
    if(tipo == 'l' and SystemLog::ativarEmTelaInfo){
        cout << "["+ SystemData::dataHora() +"][ Info        ]" << log << endl;
    }else if (tipo == 'w' and SystemLog::ativarEmTelaWarming ){
        clog << "["+ SystemData::dataHora() +"][ Warming    ]" << log << endl;
    } else if(tipo == 'e' and SystemLog::ativarEmTelaErro){
        cerr << "["+ SystemData::dataHora() +"][ Erro       ]" << log << endl;
    }

    //log em arquivo;
    chdir("/home/eduardo/Workspace/TCC-monitorWeb-Cliente");
    if(tipo == 'l' and SystemLog::ativarEmArquivoInfo){
        std::string executarConsole = "echo [" + SystemData::dataHora() + "][ Info        ] "+ log +" >> log.log";
        char *y = new char[executarConsole.length() + 1];
        std::strcpy(y, executarConsole.c_str());

        std::system(y);
        delete[] y;
    }else if (tipo == 'w' and SystemLog::ativarEmArquivoWarming){
        std::string executarConsole = "echo [" + SystemData::dataHora() + "][ Warming    ] "+ log +" >> log.log";
        char *y = new char[executarConsole.length() + 1];
        std::strcpy(y, executarConsole.c_str());

        std::system(y);
        delete[] y;
    } else if(tipo == 'e' and SystemLog::ativarEmArquivoErro){
        std::string executarConsole = "echo [" + SystemData::dataHora() + "][ Erro       ] "+ log +" >> log.log";
        char *y = new char[executarConsole.length() + 1];
        std::strcpy(y, executarConsole.c_str());

        std::system(y);
        delete[] y;
    }
}