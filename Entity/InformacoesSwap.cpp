//
// Created by eduardo on 17/10/17.
//

#include <boost/algorithm/string.hpp>
#include "InformacoesSwap.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/verbosHttp/Post.h"

InformacoesSwap::InformacoesSwap() {}

InformacoesSwap::~InformacoesSwap() {

}

void InformacoesSwap::lerInformacoesSwap(){

    try {
        chdir("/proc/");
        ConfigFile configFile("meminfo", ":");
        configFile.load();

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

    Result *result = nullptr;
    do{
        if(result != nullptr){
            delete result;
        }

        servidor.setId(srvConfig->getServidor().getId());

        string path = "/servidor/"+ to_string(srvConfig->getServidor().getId()) +"/informacoesswap/";

        Post post(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());

        lerInformacoesSwap();

        result = post.exec(toJson());
        if(result->getStatus() == 200){
            fromJson(result->getResult());
        }
        result->imprimir("InformacoesSwap");
    }
    while(result->getStatus() != 200);
    delete result;
};

string InformacoesSwap::toJson(){
    ptree pt;
    pt.put("servidor.id", servidor.getId());
    pt.put("total", getTotal());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
};

bool InformacoesSwap::fromJson(const string &json){
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    servidor.setId(pt2.get<long> ("servidor.id"));
    setTotal(pt2.get<long> ("total"));

    return true;
};



