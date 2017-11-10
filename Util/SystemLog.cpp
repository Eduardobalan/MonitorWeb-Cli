//
// Created by eduardo on 13/10/17.
//

#include <cstring>
#include <zconf.h>
#include "SystemLog.h"
#include "ConfigFile/ConfigFile.h"
#include "SystemData.h"

bool SystemLog::ativarLog;
bool SystemLog::ativarLogArquivo;
bool SystemLog::mostrarLogLog;
bool SystemLog::mostrarLogWarming;
bool SystemLog::mostrarLogErro;


void SystemLog::lerLogConf(){
    try {
        chdir("/home/eduardo/Workspace/TCC-monitorWeb-Cliente");
        ConfigFile configFile("Log.conf", ":");
        configFile.load();


        SystemLog::ativarLog = configFile.getBool("AtivarLog");
        SystemLog::ativarLogArquivo = configFile.getBool("AtivarLogArquivo");
        SystemLog::mostrarLogLog = configFile.getBool("MostrarLogLog");
        SystemLog::mostrarLogWarming = configFile.getBool("MostrarLogWarming");
        SystemLog::mostrarLogErro = configFile.getBool("MostrarLogErro");


    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void SystemLog::execLog(char tipo, const string &log){
    if(SystemLog::ativarLog){
        if(tipo == 'l' and SystemLog::mostrarLogLog){
            cout << "["+ SystemData::dataHora() +"][ Log        ]" << log << endl;
        }else if (tipo == 'w' and SystemLog::mostrarLogWarming ){
            cout << "["+ SystemData::dataHora() +"][ Warming    ]" << log << endl;
        } else if(tipo == 'e' and SystemLog::mostrarLogErro){
            cerr << "["+ SystemData::dataHora() +"][ Erro       ]" << log << endl;
        }
    }
    if(SystemLog::ativarLogArquivo){
        chdir("/home/eduardo/Workspace/TCC-monitorWeb-Cliente");

        if(tipo == 'l' and SystemLog::mostrarLogLog){
            std::string executarConsole = "echo [" + SystemData::dataHora() + "][ Log        ] "+ log +" >> log.log";
            char *y = new char[executarConsole.length() + 1];
            std::strcpy(y, executarConsole.c_str());

            std::system(y);
            delete y;
        }else if (tipo == 'w' and SystemLog::mostrarLogWarming){
            std::string executarConsole = "echo [" + SystemData::dataHora() + "][ Warming    ] "+ log +" >> log.log";
            char *y = new char[executarConsole.length() + 1];
            std::strcpy(y, executarConsole.c_str());

            std::system(y);
            delete y;
        } else if(tipo == 'e' and SystemLog::mostrarLogErro){
            std::string executarConsole = "echo [" + SystemData::dataHora() + "][ Erro       ] "+ log +" >> log.log";
            char *y = new char[executarConsole.length() + 1];
            std::strcpy(y, executarConsole.c_str());

            std::system(y);
            delete y;
        }
    }
}