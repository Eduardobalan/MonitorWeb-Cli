//
// Created by eduardo on 09/10/17.
//

#include "ServidorConfig.h"


using namespace std;


ServidorConfig::ServidorConfig() {}

ServidorConfig::~ServidorConfig() {}


std::string ServidorConfig::toJson(){
    // Write json.
    ptree pt;
    pt.put ("id", getId());
    pt.put ("servidor.id", getServidor().getId());
    pt.put ("intervaloCpu", getIntervaloCpu());
    pt.put ("intervaloMemoria", getIntervaloMemoria());
    pt.put ("intervaloSwap", getIntervaloSwap());
    pt.put ("intervaloDB", getIntervaloDB());
    pt.put ("hostMonitoramento", getHostMonitoramento());
    pt.put ("hostMonitoramento2", getHostMonitoramento2());
    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool ServidorConfig::fromJson(const std::string &json){
    // Read json.
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    //setServidor(pt2.get<Servidor> ("servidor"));
    setIntervaloCpu(pt2.get<long> ("intervaloCpu"));
    setIntervaloMemoria(pt2.get<long> ("intervaloMemoria"));
    setIntervaloSwap(pt2.get<long> ("intervaloSwap"));
    setIntervaloDB(pt2.get<long> ("intervaloDB"));
    setHostMonitoramento(pt2.get<string> ("hostMonitoramento"));
    setHostMonitoramento2(pt2.get<string> ("hostMonitoramento2"));


    return true;
}
void ServidorConfig::print() {
    //if() {
    cout << "---------ServidorConfig-------------"<< endl;
    cout << "Id: " << getId() << endl;
    cout << "Servidor: " << getServidor().getId() << endl;
    cout << "Intervalo cpu: " << getIntervaloCpu() << endl;
    cout << "Intervalo memoria: " << getIntervaloMemoria() << endl;
    cout << "Intervalo swap: " << getIntervaloSwap() << endl;
    cout << "Intervalo DB: " << getIntervaloDB() << endl;
    cout << "Host Monitoramento: " << getHostMonitoramento() << endl;
    cout << "Host Monitoramento2: " << getHostMonitoramento2() << endl;
    cout << "-------------------------"<< endl;
    //}
}

