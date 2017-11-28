//
// Created by eduardo on 13/11/17.
//

#ifndef WEBMONITOR_CLIENTE_SERVIDORCONFIGINFORMACOESDB_H
#define WEBMONITOR_CLIENTE_SERVIDORCONFIGINFORMACOESDB_H

#include <string>

using namespace std;

class ServidorConfigInformacoesDb {
private:
    long id;
    string nomeSgdb;
    string pathMain;
    long intervaloExec;
    bool ativo;

public:
    ServidorConfigInformacoesDb();

    virtual ~ServidorConfigInformacoesDb();

    //Getter and setter
    long getId() const {
        return id;
    }

    void setId(long id) {
        ServidorConfigInformacoesDb::id = id;
    }

    const string &getNomeSgdb() const {
        return nomeSgdb;
    }

    void setNomeSgdb(const string &nomeSgdb) {
        ServidorConfigInformacoesDb::nomeSgdb = nomeSgdb;
    }

    const string &getPathMain() const {
        return pathMain;
    }

    void setPathMain(const string &pathMain) {
        ServidorConfigInformacoesDb::pathMain = pathMain;
    }

    long getIntervaloExec() const {
        return intervaloExec;
    }

    void setIntervaloExec(long intervaloExec) {
        ServidorConfigInformacoesDb::intervaloExec = intervaloExec;
    }

    bool isAtivo() const {
        return ativo;
    }

    void setAtivo(bool ativo) {
        ServidorConfigInformacoesDb::ativo = ativo;
    }

};

#endif //WEBMONITOR_CLIENTE_SERVIDORCONFIGINFORMACOESDB_H
