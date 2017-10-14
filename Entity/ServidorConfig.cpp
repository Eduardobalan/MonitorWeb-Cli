//
// Created by eduardo on 09/10/17.
//

#include <thread>
#include "ServidorConfig.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/verbosHttp/Get.h"
#include "../Util/SystemLog.h"


using namespace std;


ServidorConfig::ServidorConfig() {}

ServidorConfig::~ServidorConfig() {}


void ServidorConfig::lerConfiguracoesLocais(){
    try {
        chdir("/home/eduardo/Workspace/TCC-monitorWeb-Cliente");
        ConfigFile configFile("ConfigFile.conf", ":");
        configFile.load();
        SystemLog::execLog('l',"Lendo arquivo de configurações locais.");

        setId(configFile.getInt("id"));
        servidor.setId(configFile.getInt("servidorid"));
        setIntervaloLeituraConfiguracoes(configFile.getInt("intervaloLeituraConfiguracoes"));
        setIntervaloCpu(configFile.getInt("intervaloCpu"));
        setIntervaloDB(configFile.getInt("intervaloDB"));
        setIntervaloMemoria(configFile.getInt("intervaloMemoria"));
        setIntervaloSwap(configFile.getInt("intervaloSwap"));
        setHostMonitoramento(configFile.getString("hostMonitoramento"));
        setHostMonitoramento2(configFile.getString("hostMonitoramento2"));
        setPorta(configFile.getInt("porta"));
        setPorta2(configFile.getInt("porta2"));

    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
}


void ServidorConfig::salvarConfiguracoesLocais(){
    try {
        chdir("/home/eduardo/Workspace/TCC-monitorWeb-Cliente");
        ConfigFile configFile("ConfigFile.conf", ":");

        configFile.save("id", getId());
        configFile.save("servidorid", servidor.getId());
        configFile.save("intervaloLeituraConfiguracoes", getIntervaloLeituraConfiguracoes());
        configFile.save("intervaloCpu", getIntervaloCpu());
        configFile.save("intervaloDB", getIntervaloDB());
        configFile.save("intervaloMemoria", getIntervaloMemoria());
        configFile.save("intervaloSwap", getIntervaloSwap());
        configFile.save("hostMonitoramento", getHostMonitoramento());
        configFile.save("hostMonitoramento2", getHostMonitoramento2());
        configFile.save("porta", getPorta());
        configFile.save("porta2", getPorta2());

        configFile.commit();
        SystemLog::execLog('l',"Arquivo de configurações locais atualizados com API.");

    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void ServidorConfig::sincronizarConfigLocalComApi(ServidorConfig *srvConfig){
    
    Result *resultServidorConfig;
    do{
        string path = "/servidor/"+ to_string(srvConfig->getServidor().getId()) +"/servidorconfiguracoes/"+to_string(srvConfig->getId());
        Get getServidorConfig(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
        resultServidorConfig = getServidorConfig.exec();
        if(resultServidorConfig->getStatus() == 200){
            srvConfig->fromJson(resultServidorConfig->getResult());
            srvConfig->salvarConfiguracoesLocais();
            SystemLog::execLog('l',"Lendo api configurações do servidor:."+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        }else{
            SystemLog::execLog('e',"Lendo api configurações do servidor: Status:"+resultServidorConfig->getResult() +" erro:"+ resultServidorConfig->getError());
        }
        usleep(srvConfig->getIntervaloLeituraConfiguracoes()*100000);
    }
    while(true);

};

void ServidorConfig::threadSincronizarConfigLocalComApi(ServidorConfig *srvConfig){
    SystemLog::execLog('l',"Iniciando Thread Sincronizar Config local com API");
    std::thread threadx(sincronizarConfigLocalComApi, srvConfig);
    threadx.detach();
};

std::string ServidorConfig::toJson(){
    SystemLog::execLog('l',"Tranformando Objeto ServidorConfig em Json;");
    ptree pt;
    pt.put ("id", getId());
    pt.put ("servidor.id", getServidor().getId());
    pt.put ("intervaloLeituraConfiguracoes", getIntervaloLeituraConfiguracoes());
    pt.put ("intervaloCpu", getIntervaloCpu());
    pt.put ("intervaloMemoria", getIntervaloMemoria());
    pt.put ("intervaloSwap", getIntervaloSwap());
    pt.put ("intervaloDB", getIntervaloDB());
    pt.put ("hostMonitoramento", getHostMonitoramento());
    pt.put ("hostMonitoramento2", getHostMonitoramento2());
    pt.put ("porta", getPorta());
    pt.put ("porta2", getPorta2());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool ServidorConfig::fromJson(const std::string &json){
    SystemLog::execLog('l',"Trasformando o json em objeto");
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    //setServidor(pt2.get<Servidor> ("servidor"));
    setIntervaloLeituraConfiguracoes(pt2.get<long> ("intervaloLeituraConfiguracoes"));
    setIntervaloCpu(pt2.get<long> ("intervaloCpu"));
    setIntervaloMemoria(pt2.get<long> ("intervaloMemoria"));
    setIntervaloSwap(pt2.get<long> ("intervaloSwap"));
    setIntervaloDB(pt2.get<long> ("intervaloDB"));
    setHostMonitoramento(pt2.get<string> ("hostMonitoramento"));
    setHostMonitoramento2(pt2.get<string> ("hostMonitoramento2"));
    setPorta(pt2.get<long> ("porta"));
    setPorta2(pt2.get<long> ("porta2"));



    return true;
}
void ServidorConfig::print() {

    cout << "---------ServidorConfig-------------"<< endl;
    cout << "Id: " << getId() << endl;
    cout << "Servidor: " << getServidor().getId() << endl;
    cout << "Intervalo Leitura Configurações: " << getIntervaloLeituraConfiguracoes() << endl;
    cout << "Intervalo cpu: " << getIntervaloCpu() << endl;
    cout << "Intervalo memoria: " << getIntervaloMemoria() << endl;
    cout << "Intervalo swap: " << getIntervaloSwap() << endl;
    cout << "Intervalo DB: " << getIntervaloDB() << endl;
    cout << "Host Monitoramento: " << getHostMonitoramento() << endl;
    cout << "Host Monitoramento2: " << getHostMonitoramento2() << endl;
    cout << "porta: " << getPorta() << endl;
    cout << "porta2: " << getPorta2() << endl;
    cout << "-------------------------"<< endl;

}

