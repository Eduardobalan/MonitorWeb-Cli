//
// Created by eduardo on 17/10/17.
//

#include <boost/algorithm/string.hpp>
#include "InformacoesSwap.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/SystemLog.h"
#include "../Util/verbosHttp/Post.h"

InformacoesSwap::InformacoesSwap() {}

InformacoesSwap::~InformacoesSwap() {

}

void InformacoesSwap::lerInformacoesSwap(){

    try {
        chdir("/proc/");
        ConfigFile configFile("meminfo", ":");
        configFile.load();
        SystemLog::execLog('l',"InformacoesSwap: lendo InformacoesSwap");


        string SwapTotal =  configFile.getString("SwapTotal");
        boost::erase_all(SwapTotal, " KB");
        setTotal(std::stol(SwapTotal,nullptr,0));


    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
};

void InformacoesSwap::monitorarInformacoesSwap(ServidorConfig *srvConfig){

    servidor.setId(srvConfig->getServidor().getId());

    string path = "/servidor/"+ to_string(srvConfig->getServidor().getId()) +"/informacoesswap/";

    Post post(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
    Result *result;
    do{
        lerInformacoesSwap();

        result = post.exec(toJson());
        SystemLog::execLog('l',"InformacoesSwap : "+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        if(result->getStatus() == 200){
            fromJson(result->getResult());
            SystemLog::execLog('l',"InformacoesSwap Resultado: "+result->getResult());
        }else{
            SystemLog::execLog('e',"InformacoesSwap: Status:"+result->getResult() +" erro:"+ result->getError());
            SystemLog::execLog('e',"InformacoesSwap json enviado: "+toJson());
        }
    }
    while(result->getStatus() != 200);

};

string InformacoesSwap::toJson(){
    SystemLog::execLog('l',"InformacoesSwap: Tranformando Objeto em Json");
    ptree pt;
    pt.put("servidor.id", servidor.getId());
    pt.put("total", getTotal());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
};

bool InformacoesSwap::fromJson(const string &json){
    SystemLog::execLog('l',"InformacoesSwap: Trasformando o json em objeto");
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    servidor.setId(pt2.get<long> ("servidor.id"));
    servidor.setNome(pt2.get<string> ("servidor.nome"));
    setTotal(pt2.get<long> ("total"));

    return true;
};



