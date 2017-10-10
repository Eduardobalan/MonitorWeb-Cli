//
// Created by eduardo on 13/09/17.
//

#include <iostream>
#include "Servidor.h"

using namespace std;




Servidor::Servidor() {}

Servidor::~Servidor() {

}


std::string Servidor::toJson(){
    // Write json.
    ptree pt;
    pt.put ("id", getId());
    pt.put ("nome", getNome());
    pt.put ("empresa", getNome());
    pt.put ("observacao", getObservacao());
    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool Servidor::fromJson(const std::string &json){
    // Read json.
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    setNome(pt2.get<string> ("nome"));
    setEmpresa(pt2.get<string> ("empresa"));
    setObservacao(pt2.get<string> ("observacao"));

    return true;
}




