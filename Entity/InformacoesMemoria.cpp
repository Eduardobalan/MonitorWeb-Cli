//
// Created by eduardo on 16/10/17.
//

#include <boost/algorithm/string.hpp>
#include "InformacoesMemoria.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/SystemLog.h"
#include "../Util/verbosHttp/Post.h"

InformacoesMemoria::InformacoesMemoria() {}

InformacoesMemoria::~InformacoesMemoria() {

}
void InformacoesMemoria::lerInformacoesMemoria(){

    try {
        chdir("/proc/");
        ConfigFile configFile("meminfo", ":");
        configFile.load();
        SystemLog::execLog('l',"InformacoesMemoria: lendo InformacoesMemoria");


        string cacheSize =  configFile.getString("MemTotal");
        boost::erase_all(cacheSize, " KB");
        setTotal(std::stol(cacheSize,nullptr,0));


    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
}


void InformacoesMemoria::monitorarInformacoesMemoria(ServidorConfig *srvConfig){

    servidor.setId(srvConfig->getServidor().getId());

    string path = "/servidor/"+ to_string(srvConfig->getServidor().getId()) +"/informacoesmemoria/";

    Post post(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
    Result *result;
    do{
        lerInformacoesMemoria();

        result = post.exec(toJson());
        SystemLog::execLog('l',"InformacoesMemoria : "+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        if(result->getStatus() == 200){
            fromJson(result->getResult());
            SystemLog::execLog('l',"InformacoesMemoria Resultado: "+result->getResult());
        }else{
            SystemLog::execLog('e',"InformacoesMemoria: Status:"+result->getResult() +" erro:"+ result->getError());
            SystemLog::execLog('e',"InformacoesMemoria json enviado: "+toJson());
        }
    }
    while(result->getStatus() != 200);
}

std::string InformacoesMemoria::toJson(){
    SystemLog::execLog('l',"InformacoesMemoria: Tranformando Objeto em Json");
    ptree pt;
    pt.put("servidor.id", servidor.getId());
    pt.put("total", getTotal());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool InformacoesMemoria::fromJson(const std::string &json){
    SystemLog::execLog('l',"InformacoesMemoria: Trasformando o json em objeto");
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    servidor.setId(pt2.get<long> ("servidor.id"));
    servidor.setNome(pt2.get<string> ("servidor.nome"));
    setTotal(pt2.get<long> ("total"));

    return true;
}
