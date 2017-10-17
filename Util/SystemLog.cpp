//
// Created by eduardo on 13/10/17.
//

#include <cstring>
#include <zconf.h>
#include "SystemLog.h"
#include "ConfigFile/ConfigFile.h"

bool SystemLog::ativarLog;
bool SystemLog::ativarLogArquivo;
bool SystemLog::mostrarLogLog;
bool SystemLog::mostrarLogWorming;
bool SystemLog::mostrarLogErro;


void SystemLog::lerLogConf(){
    try {
        chdir("/home/eduardo/Workspace/TCC-monitorWeb-Cliente");
        ConfigFile configFile("Log.conf", ":");
        configFile.load();


        SystemLog::ativarLog = configFile.getBool("AtivarLog");
        SystemLog::ativarLogArquivo = configFile.getBool("AtivarLogArquivo");
        SystemLog::mostrarLogLog = configFile.getBool("MostrarLogLog");
        SystemLog::mostrarLogWorming = configFile.getBool("MostrarLogWorming");
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
            cout << "[ log        ]" << log << endl;
        }else if (tipo == 'w' and SystemLog::mostrarLogWorming ){
            cout << "[ worming    ]" << log << endl;
        } else if(tipo == 'e' and SystemLog::mostrarLogErro){
            cerr << "[ erro       ]" << log << endl;
        }
    }
    if(SystemLog::ativarLogArquivo){
        chdir("/home/eduardo/Workspace/TCC-monitorWeb-Cliente");

        if(tipo == 'l' and SystemLog::mostrarLogLog){
            std::string executarConsole = "echo [ log        ] "+ log +" >> log.log";
            char *y = new char[executarConsole.length() + 1];
            std::strcpy(y, executarConsole.c_str());

            std::system(y);
        }else if (tipo == 'w' and SystemLog::mostrarLogWorming){
            std::string executarConsole = "echo [ worming    ] "+ log +" >> log.log";
            char *y = new char[executarConsole.length() + 1];
            std::strcpy(y, executarConsole.c_str());

            std::system(y);
        } else if(tipo == 'e' and SystemLog::mostrarLogErro){
            std::string executarConsole = "echo [ erro       ] "+ log +" >> log.log";
            char *y = new char[executarConsole.length() + 1];
            std::strcpy(y, executarConsole.c_str());

            std::system(y);
        }
    }
}