//
// Created by eduardo on 13/10/17.
//

#ifndef WEBMONITOR_CLIENTE_SYSTEMLOG_H
#define WEBMONITOR_CLIENTE_SYSTEMLOG_H

#include <iostream>
#include <string>

using namespace std;

class SystemLog {
private:
    static bool mostrarLogLog;
    static bool mostrarLogWorming;
    static bool mostrarLogErro;
    static bool ativarLog;
    static bool ativarLogArquivo;
public:


    static void lerLogConf();

    static void execLog(char tipo,const string &log);

    // ------ Getter end Setter

    static bool isMostrarLogLog() {
        return mostrarLogLog;
    }

    static void setMostrarLogLog(bool mostrarLogLog) {
        SystemLog::mostrarLogLog = mostrarLogLog;
    }

    static bool isMostrarLogWorming() {
        return mostrarLogWorming;
    }

    static void setMostrarLogWorming(bool mostrarLogWorming) {
        SystemLog::mostrarLogWorming = mostrarLogWorming;
    }

    static bool isMostrarLogErro() {
        return mostrarLogErro;
    }

    static void setMostrarLogErro(bool mostrarLogErro) {
        SystemLog::mostrarLogErro = mostrarLogErro;
    }

    static bool isAtivarLogArquivo() {
        return ativarLogArquivo;
    }

    static void setAtivarLogArquivo(bool ativarLogArquivo) {
        SystemLog::ativarLogArquivo = ativarLogArquivo;
    }

    static bool isAtivarLog() {
        return ativarLog;
    }

    static bool setAtivarLog(bool ativarLog) {
        SystemLog::ativarLog = ativarLog;
    }
};


#endif //WEBMONITOR_CLIENTE_SYSTEMLOG_H
