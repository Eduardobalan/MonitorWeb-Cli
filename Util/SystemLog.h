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
    static bool ativarEmTelaInfo;
    static bool ativarEmTelaWarning;
    static bool ativarEmTelaErro;
    static bool ativarEmArquivoInfo;
    static bool ativarEmArquivoWarning;
    static bool ativarEmArquivoErro;
public:

    static void lerLogConf();

    static void execLog(char tipo,const string &log);

    // ------ Getter end Setter

    static bool isAtivarEmTelaInfo() {
        return ativarEmTelaInfo;
    }

    static void setAtivarEmTelaInfo(bool ativarEmTelaInfo) {
        SystemLog::ativarEmTelaInfo = ativarEmTelaInfo;
    }

    static bool isAtivarEmArquivoInfo() {
        return ativarEmArquivoInfo;
    }

    static void setAtivarEmArquivoInfo(bool ativarEmArquivoInfo) {
        SystemLog::ativarEmArquivoInfo = ativarEmArquivoInfo;
    }

    static bool isAtivarEmTelaWarning() {
        return ativarEmTelaWarning;
    }

    static void setAtivarEmTelaWarning(bool ativarEmTelaWarning) {
        SystemLog::ativarEmTelaWarning = ativarEmTelaWarning;
    }

    static bool isAtivarEmTelaErro() {
        return ativarEmTelaErro;
    }

    static void setAtivarEmTelaErro(bool ativarEmTelaErro) {
        SystemLog::ativarEmTelaErro = ativarEmTelaErro;
    }

    static bool isAtivarEmArquivoWarning() {
        return ativarEmArquivoWarning;
    }

    static void setAtivarEmArquivoWarning(bool ativarEmArquivoWarning) {
        SystemLog::ativarEmArquivoWarning= ativarEmArquivoWarning;
    }

    static bool isAtivarEmArquivoErro() {
        return ativarEmArquivoErro;
    }

    static void setAtivarEmArquivoErro(bool ativarEmArquivoErro) {
        SystemLog::ativarEmArquivoErro = ativarEmArquivoErro;
    }
};


#endif //WEBMONITOR_CLIENTE_SYSTEMLOG_H
