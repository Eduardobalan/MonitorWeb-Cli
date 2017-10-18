//
// Created by eduardo on 17/10/17.
//

#include "InformacoesDb.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "../Util/verbosHttp/Post.h"


InformacoesDb::InformacoesDb() {}

InformacoesDb::~InformacoesDb() {

};

void InformacoesDb::lerInformacoesDb(ServidorConfig *srvConfig){
    try {
        char *path = new char[srvConfig->getPostgresPathMain().length() + 1];
        std::strcpy(path, srvConfig->getPostgresPathMain().c_str());

        chdir(path);
        ConfigFile configFile("postgresql.conf", "=");

        configFile.load();
        SystemLog::execLog('l',"InformacoesDb: lendo InformacoesDb");

        setListenAddresses(configFile.getString("listen_addresses"));

        setPort(configFile.getString("port"));
        setMaxConnections(configFile.getString("max_connections"));
        setSsl(configFile.getString("ssl"));
        setSharedBuffers(configFile.getString("shared_buffers"));
        setTempBuffers(configFile.getString("temp_buffers"));
        setWorkMem(configFile.getString("work_mem"));
        setMaintenanceWorkMem(configFile.getString("maintenance_work_mem"));
        setReplacementWortTuples(configFile.getString("replacement_sort_tuples"));
        setMaxStackDepth(configFile.getString("max_stack_depth"));
        setMaxPreparedTransactions(configFile.getString("max_prepared_transactions"));


    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
};

void InformacoesDb::monitorarInformacoesDb(ServidorConfig *srvConfig){

    servidor.setId(srvConfig->getServidor().getId());

    string path = "/servidor/"+ to_string(srvConfig->getServidor().getId()) +"/informacoesdb/";

    Post post(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());
    Result *result;
    do{
        lerInformacoesDb(srvConfig);

        result = post.exec(toJson());
        SystemLog::execLog('l',"InformacoesDb : "+srvConfig->getHostMonitoramento()+":"+to_string(srvConfig->getPorta())+ path);
        if(result->getStatus() == 200){
            fromJson(result->getResult());
            SystemLog::execLog('l',"InformacoesDb Resultado: "+result->getResult());
        }else{
            SystemLog::execLog('e',"InformacoesDb: Status:"+result->getResult() +" erro:"+ result->getError());
            SystemLog::execLog('e',"InformacoesDb json enviado: "+toJson());
        }
    }
    while(result->getStatus() != 200);
};

string InformacoesDb::toJson(){
    SystemLog::execLog('l',"InformacoesDb: Tranformando Objeto em Json");
    ptree pt;
    pt.put("servidor.id", servidor.getId());
    pt.put("listenAddresses", getListenAddresses());
    pt.put("port", getPort());
    pt.put("maxConnections", getMaxConnections());
    pt.put("ssl", getSsl());
    pt.put("sharedBuffers", getSharedBuffers());
    pt.put("tempBuffers", getTempBuffers());
    pt.put("workMem", getWorkMem());
    pt.put("maintenanceWorkMem", getMaintenanceWorkMem());
    pt.put("replacementWortTuples", getReplacementWortTuples());
    pt.put("maxStackDepth", getMaxStackDepth());
    pt.put("maxPreparedTransactions", getMaxPreparedTransactions());


    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
};

bool InformacoesDb::fromJson(const string &json){
    SystemLog::execLog('l',"InformacoesDb: Trasformando o json em objeto");
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    servidor.setId(pt2.get<long> ("servidor.id"));
    setListenAddresses(pt2.get<string> ("listenAddresses"));
    setPort(pt2.get<string> ("port"));
    setMaxConnections(pt2.get<string> ("maxConnections"));
    setSsl(pt2.get<string> ("ssl"));
    setSharedBuffers(pt2.get<string> ("sharedBuffers"));
    setTempBuffers(pt2.get<string> ("tempBuffers"));
    setWorkMem(pt2.get<string> ("workMem"));
    setMaintenanceWorkMem(pt2.get<string> ("maintenanceWorkMem"));
    setReplacementWortTuples(pt2.get<string> ("replacementWortTuples"));
    setMaxStackDepth(pt2.get<string> ("maxStackDepth"));
    setMaxPreparedTransactions(pt2.get<string> ("maxPreparedTransactions"));

    return true;
}
