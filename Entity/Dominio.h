//
// Created by eduardo on 29/09/17.
//
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#ifndef WEBMONITOR_CLIENTE_DOMINIO_H
#define WEBMONITOR_CLIENTE_DOMINIO_H


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;
using std::cout;

class Dominio{
private:
    long id;
    string nome;
    string observacao;

public:
//    Dominio();
//
//    virtual ~Dominio();

    long getId() const;

    void setId(long id);

    const string &getNome() const;

    void setNome(const string &nome);

    const string &getObservacao() const;

    void setObservacao(const std::string &observacao);

    bool fromJson(const string &json);

    string toJson();


};

#endif //WEBMONITOR_CLIENTE_DOMINIO_H
