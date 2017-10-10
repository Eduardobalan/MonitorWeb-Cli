//
// Created by eduardo on 14/09/17.
//
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Servidor.h"

#ifndef WEBMONITOR_CLIENTE_INFORMACOESCPU_H
#define WEBMONITOR_CLIENTE_INFORMACOESCPU_H

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;
using std::cout;

class InformacoesCpu {

private:
    long Id;
    Servidor *servidor;
    string nome;
    long cacheSize;
    long cpuCores;
    //numero de cores virtuais
    long siblings;

public:
    InformacoesCpu();
    ~InformacoesCpu();

    void print();

    void lerInformacoesCpu();

    bool fromJson(const string &json);

    string toJson();

    //======== Getter end Setter

    long getId() const {
        return Id;
    }

    void setId(long Id) {
        InformacoesCpu::Id = Id;
    }

    Servidor *getServidor() const {
        return servidor;
    }

    void setServidor(Servidor *servidor) {
        InformacoesCpu::servidor = servidor;
    }

    const string &getNome() const {
        return nome;
    }

    void setNome(const string &nome) {
        InformacoesCpu::nome = nome;
    }

    long getCacheSize() const {
        return cacheSize;
    }

    void setCacheSize(long cacheSize) {
        InformacoesCpu::cacheSize = cacheSize;
    }

    long getCpuCores() const {
        return cpuCores;
    }

    void setCpuCores(long cpuCores) {
        InformacoesCpu::cpuCores = cpuCores;
    }

    long getSiblings() const {
        return siblings;
    }

    void setSiblings(long siblings) {
        InformacoesCpu::siblings = siblings;
    }

};


#endif //WEBMONITOR_CLIENTE_INFORMACOESCPU_H
