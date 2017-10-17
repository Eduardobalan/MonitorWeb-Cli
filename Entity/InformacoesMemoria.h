//
// Created by eduardo on 16/10/17.
//

#ifndef WEBMONITOR_CLIENTE_INFORMACOESMEMORIA_H
#define WEBMONITOR_CLIENTE_INFORMACOESMEMORIA_H


#include "ServidorConfig.h"

class InformacoesMemoria {
private:
    long Id;
    long total;
    Servidor servidor;
public:
    InformacoesMemoria();

    virtual ~InformacoesMemoria();

    void lerInformacoesMemoria();

    void monitorarInformacoesMemoria(ServidorConfig *srvConfig);

    bool fromJson(const string &json);

    string toJson();

    //getter and setter

    long getId() const {
        return Id;
    }

    void setId(long Id) {
        InformacoesMemoria::Id = Id;
    }

    long getTotal() const {
        return total;
    }

    void setTotal(long total) {
        InformacoesMemoria::total = total;
    }

    const Servidor &getServidor() const {
        return servidor;
    }

    void setServidor(const Servidor &servidor) {
        InformacoesMemoria::servidor = servidor;
    }
};


#endif //WEBMONITOR_CLIENTE_INFORMACOESMEMORIA_H
