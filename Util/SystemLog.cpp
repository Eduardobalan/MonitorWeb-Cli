//
// Created by eduardo on 13/10/17.
//

#include "SystemLog.h"

bool SystemLog::ativarLog;
bool SystemLog::ativarLogArquivo;

void SystemLog::execLog(char tipo, const string &log){
    if(SystemLog::ativarLog){
        if(tipo == 'l'){
            cout << "[ log     ]" << log << endl;
        }else if (tipo == 'w'){
            cout << "[ worming ]" << log << endl;
        } else {
            cerr << "[ erro    ]" << log << endl;
        }

    }
    if(SystemLog::ativarLogArquivo){
        //char*  log + ">> log.log";
        //std::system("'teste' > log.log");
    }
}