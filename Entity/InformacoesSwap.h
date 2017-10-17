//
// Created by eduardo on 17/10/17.
//

#ifndef WEBMONITOR_CLIENTE_INFORMACOESSWAP_H
#define WEBMONITOR_CLIENTE_INFORMACOESSWAP_H


#include "Servidor.h"
#include "ServidorConfig.h"

class InformacoesSwap {
private:
    long Id;
    long total;
    Servidor servidor;
public:

    InformacoesSwap();

    virtual ~InformacoesSwap();

    void lerInformacoesSwap();

    void monitorarInformacoesSwap(ServidorConfig *srvConfig);

    bool fromJson(const string &json);

    string toJson();

    //getter and setter

    long getId() const {
        return Id;
    }

    void setId(long Id) {
        InformacoesSwap::Id = Id;
    }

    long getTotal() const {
        return total;
    }

    void setTotal(long total) {
        InformacoesSwap::total = total;
    }

    const Servidor &getServidor() const {
        return servidor;
    }

    void setServidor(const Servidor &servidor) {
        InformacoesSwap::servidor = servidor;
    }
};


#endif //WEBMONITOR_CLIENTE_INFORMACOESSWAP_H
