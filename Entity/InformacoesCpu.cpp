//
// Created by eduardo on 14/09/17.
//

#include "InformacoesCpu.h"

using namespace std;


InformacoesCpu::InformacoesCpu() {
    cout << "contrutor InformacoesCpu\n";
};

InformacoesCpu::~InformacoesCpu() {
    std::cout << "destrutor InformacoesCpu\n";
}


void InformacoesCpu::lerInformacoesCpu(){
    char teste[60] ;
    system("cat /proc/cpuinfo | grep \"cpu cores\" | sort  | wc -l ");
    setCpuCores(system("cat /proc/cpuinfo | grep \"cpu cores\" | sort  | wc -l"));
    cout << teste;
}

std::string InformacoesCpu::toJson(){
    // Write json.
    ptree pt;
    pt.put ("servidor.id", servidor->getId());
    pt.put ("nome", getNome());
    pt.put ("cacheSize", getCacheSize());
    pt.put ("cpuCores", getCpuCores());
    pt.put ("siblings", getSiblings());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool InformacoesCpu::fromJson(const std::string &json){
    // Read json.

    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    setNome(pt2.get<string> ("nome"));
    setCacheSize(pt2.get<long> ("cacheSize"));
    setCpuCores(pt2.get<long> ("cpuCores"));
    setSiblings(pt2.get<long> ("siblings"));

    return true;
}

void InformacoesCpu::print(){
    cout << getId() << endl;
    //cout << servidor->getId() << endl;
    cout <<  getNome() << endl;
    cout <<  getCacheSize() << endl;
    cout << getCpuCores() << endl;
    cout << getSiblings() << endl;
};




