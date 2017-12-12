//
// Created by eduardo on 17/10/17.
//

#include "MonitoramentoPostgresInformacoes.h"
#include "../Util/ConfigFile/ConfigFile.h"
#include "ServidorConfigDb.h"
#include "../Util/resource/Resource.h"


MonitoramentoPostgresInformacoes::MonitoramentoPostgresInformacoes() {
    servidorConfigInformacoesDb = new ServidorConfigInformacoesDb();
}

MonitoramentoPostgresInformacoes::~MonitoramentoPostgresInformacoes() {
    if(servidorConfigInformacoesDb != nullptr){
        delete servidorConfigInformacoesDb;
    }
    if(threadx != nullptr){
        delete threadx;
    }
};

void MonitoramentoPostgresInformacoes::lerMonitoramentoPostgresInformacoes(ServidorConfigInformacoesDb *servidorConfigInformacoesDb){
    try {
       char *path = new char[servidorConfigInformacoesDb->getPathMain().length() + 1];
       std::strcpy(path, servidorConfigInformacoesDb->getPathMain().c_str());

        chdir(path);
        ConfigFile configFile("postgresql.conf", "=");

        configFile.load();

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


        delete[] path;
    } catch (FileNotFoundException &ex) {
        std::cerr << ex.what() << std::endl;
    } catch (InvalidPropertyName &ex) {
        std::cerr << ex.what() << std::endl;
    }
};

void MonitoramentoPostgresInformacoes::monitorarMonitoramentoPostgresInformacoes(ServidorConfig *srvConfig, ServidorConfigInformacoesDb *servidorConfigInformacoesDb, MonitoramentoPostgresInformacoes *monitoramentoPostgresInformacoes){

    Result *result = nullptr;
    do{
        sleep(servidorConfigInformacoesDb->getIntervaloExec());
        if(monitoramentoPostgresInformacoes->getServidorConfigInformacoesDb()->isAtivo()) {
            string path = "/servidor/informacoes/"+to_string(monitoramentoPostgresInformacoes->getServidorConfigInformacoesDb()->getId())+"/monitoramentopostgresinformacoes";
            Resource resource(path, srvConfig->getHostMonitoramento(), srvConfig->getPorta());

            monitoramentoPostgresInformacoes->lerMonitoramentoPostgresInformacoes(servidorConfigInformacoesDb);

            result = resource.post(monitoramentoPostgresInformacoes->toJson());

            result->imprimir("MonitoramentoPostgresInformacoes{"+ monitoramentoPostgresInformacoes->threadId +"}");

            delete result;
        }else{
            SystemLog::execLog('w',"MonitoramentoPostgresInformacoes{" + monitoramentoPostgresInformacoes->threadId + "}: Registro de informacoes esta desativado.");
        }
    }
    while(srvConfig->isFicarMonitorando());
};

void MonitoramentoPostgresInformacoes::threadMonitorarMonitoramentoPostgresInformacoes(ServidorConfig *srvConfig, ServidorConfigInformacoesDb *servidorConfigInformacoesDb, MonitoramentoPostgresInformacoes *monitoramentoPostgresInformacoes){
    SystemLog::execLog('l',"MonitoramentoPostgresInformacoes: Iniciando uma Thread de Sincronizar local com API");
    threadx = new std::thread(monitorarMonitoramentoPostgresInformacoes, srvConfig, servidorConfigInformacoesDb, monitoramentoPostgresInformacoes);

    //Salva o id da thread no MonitoramentoPostgresInformacoes.
    auto myid = threadx->get_id();
    stringstream ss;
    ss << myid;
    threadId = ss.str();
};

string MonitoramentoPostgresInformacoes::toJson(){
    ptree pt;
    pt.put("servidorConfigInformacoesDb.id", servidorConfigInformacoesDb->getId());
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

bool MonitoramentoPostgresInformacoes::fromJson(const string &json){
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setId(pt2.get<long> ("id"));
    servidorConfigInformacoesDb->setId(pt2.get<long> ("servidorConfigInformacoesDb.id"));
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
