//
// Created by eduardo on 14/09/17.
//

#include "InformacoesCpu.h"
#include "ServidorConfig.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/SystemLog.h"
#include <boost/algorithm/string.hpp>

using namespace std;


InformacoesCpu::InformacoesCpu() {
};

InformacoesCpu::~InformacoesCpu() {

}


void InformacoesCpu::lerInformacoesCpu(){

    try {
        chdir("/proc/");
        ConfigFile configFile("cpuinfo", ":");
        configFile.load();
        SystemLog::execLog('l',"InformacoesCpu: lendo InformacoesCpu");

        setNome(configFile.getString("model name"));

        string cacheSize =  configFile.getString("cache size");
        boost::erase_all(cacheSize, " KB");
        setCacheSize(std::stol(cacheSize,nullptr,0));

        setCpuCores(configFile.getInt("cpu cores"));
        setSiblings(configFile.getInt("siblings"));

    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
}


void InformacoesCpu::monitorarInformacoesCpu(ServidorConfig *srvConfig){

    servidor.setId(srvConfig->getServidor().getId());

    string path = "/servidor/"+ to_string(srvConfig->getServidor().getId()) +"/informacoescpu/";

    Post post(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
    Result *result;
    do{
        lerInformacoesCpu();

        result = post.exec(toJson());
        SystemLog::execLog('l',"InformacoesCpu : "+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        if(result->getStatus() == 200){
            fromJson(result->getResult());
            SystemLog::execLog('l',"InformacoesCpu Resultado: "+result->getResult());
        }else{
            SystemLog::execLog('e',"InformacoesCpu: Status:"+result->getResult() +" erro:"+ result->getError());
            SystemLog::execLog('e',"InformacoesCpu json enviado: "+toJson());
        }
    }
    while(result->getStatus() != 200);
}

std::string InformacoesCpu::toJson(){
    SystemLog::execLog('l',"InformacoesCpu: Tranformando Objeto em Json");
    ptree pt;
    pt.put("servidor.id", servidor.getId());
    pt.put("nome", getNome());
    pt.put("cacheSize", getCacheSize());
    pt.put("cpuCores", getCpuCores());
    pt.put("siblings", getSiblings());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool InformacoesCpu::fromJson(const std::string &json){
    SystemLog::execLog('l',"ServidorConfig: Trasformando o json em objeto");
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    servidor.setId(pt2.get<long> ("servidor.id"));
    servidor.setNome(pt2.get<string> ("servidor.nome"));
    setNome(pt2.get<string> ("nome"));
    setCacheSize(pt2.get<long> ("cacheSize"));
    setCpuCores(pt2.get<long> ("cpuCores"));
    setSiblings(pt2.get<long> ("siblings"));

    return true;
}

void InformacoesCpu::print(){
    cout << "Id: " << getId() << endl;
    cout << "servidor.id: " << servidor.getId() << endl;
    cout << "servidor.nome: " << servidor.getNome() << endl;
    cout << "nome: " << getNome() << endl;
    cout << "size: " << getCacheSize() << endl;
    cout << "cores: " << getCpuCores() << endl;
    cout << "siblings : " << getSiblings() << endl;
}





