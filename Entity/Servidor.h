//
// Created by eduardo on 13/09/17.
//
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Generic/GenericEntity.h"

#ifndef WEBMONITOR_CLIENTE_SERVIDOR_H
#define WEBMONITOR_CLIENTE_SERVIDOR_H

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;
using std::cout;

class Servidor{

private:
    long id;
    string nome;
    string empresa;
    string observacao;
public:

    Servidor();

    virtual ~Servidor();

    bool fromJson(const string &json);

    string toJson();


    //=========== Getter and Setter =========
    long getId() const {
        return id;
    }

    void setId(long id) {
        Servidor::id = id;
    }

    const string &getNome() const {
        return nome;
    }

    void setNome(const string &nome) {
        Servidor::nome = nome;
    }

    const string &getEmpresa() const {
        return empresa;
    }

    void setEmpresa(const string &empresa) {
        Servidor::empresa = empresa;
    }

    const string &getObservacao() const {
        return observacao;
    }

    void setObservacao(const string &observacao) {
        Servidor::observacao = observacao;
    }
};

#endif //WEBMONITOR_CLIENTE_SERVIDOR_H
