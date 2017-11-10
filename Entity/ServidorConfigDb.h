//
// Created by eduardo on 30/10/17.
//

#ifndef WEBMONITOR_CLIENTE_SERVIDROCONFIGDB_H
#define WEBMONITOR_CLIENTE_SERVIDROCONFIGDB_H

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <map>
#include "Servidor.h"
#include "ServidorConfig.h"
#include "ServidorConfigDb.h"


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;
using std::cout;

class ServidorConfigDb {
private:
    long id;
    Servidor servidor;
    string nomeSgdb;
    string sgdbTipoExec;
    string nomeDb;
    string pathMain;
    string ip;
    long porta;
    string versao;
    long intervaloExec;
public:
    ServidorConfigDb() {  }

    virtual ~ServidorConfigDb();

    long getId() const {
        return id;
    }

    void setId(long id) {
        ServidorConfigDb::id = id;
    }

    const Servidor &getServidor() const {
        return servidor;
    }

    void setServidor(const Servidor &servidor) {
        ServidorConfigDb::servidor = servidor;
    }

    const string &getNomeSgdb() const {
        return nomeSgdb;
    }

    void setNomeSgdb(const string &nomeSgdb) {
        ServidorConfigDb::nomeSgdb = nomeSgdb;
    }

    const string &getNomeDb() const {
        return nomeDb;
    }

    const string &getSgdbTipoExec() const {
        return sgdbTipoExec;
    }

    void setSgdbTipoExec(const string &sgdbTipoExec) {
        ServidorConfigDb::sgdbTipoExec = sgdbTipoExec;
    }

    const string &getIp() const {
        return ip;
    }

    void setIp(const string &ip) {
        ServidorConfigDb::ip = ip;
    }

    void setNomeDb(const string &nomeDb) {
        ServidorConfigDb::nomeDb = nomeDb;
    }

    const string &getPathMain() const {
        return pathMain;
    }

    void setPathMain(const string &pathMain) {
        ServidorConfigDb::pathMain = pathMain;
    }

    long getPorta() const {
        return porta;
    }

    void setPorta(long porta) {
        ServidorConfigDb::porta = porta;
    }

    const string &getVersao() const {
        return versao;
    }

    void setVersao(const string &versao) {
        ServidorConfigDb::versao = versao;
    }

    long getIntervaloExec() const {
        return intervaloExec;
    }

    void setIntervaloExec(long intervaloExec) {
        ServidorConfigDb::intervaloExec = intervaloExec;
    }
};


#endif //WEBMONITOR_CLIENTE_SERVIDROCONFIGDB_H
