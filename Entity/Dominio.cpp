//
// Created by eduardo on 29/09/17.
//

#include "Dominio.h"


//Dominio::Dominio() {}
//
//Dominio::~Dominio() {
//
//}

long Dominio::getId() const {
    return id;
}

void Dominio::setId(long id) {
    Dominio::id = id;
}

const std::string &Dominio::getNome() const {
    return nome;
}

void Dominio::setNome(const std::string &nome) {
    Dominio::nome = nome;
}

const std::string &Dominio::getObservacao() const {
    return observacao;
}

void Dominio::setObservacao(const std::string &observacao) {
    Dominio::observacao = observacao;
}

std::string Dominio::toJson(){
    // Write json.
    ptree pt;
    pt.put ("id", getId());
    pt.put ("nome.teste", getNome());
    pt.put ("observacao", getObservacao());
    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool Dominio::fromJson(const std::string &json){
    // Read json.
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    setNome(pt2.get<string> ("nome.teste"));
    setObservacao(pt2.get<string> ("observacao"));

    return true;
}


