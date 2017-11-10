//
// Created by eduardo on 08/11/17.
//

#include "SystemData.h"

struct tm* SystemData::horarioLocal(){
    time_t timer;
    time(&timer); // Obtem informações de data e hora

    return localtime(&timer); // Converte a hora atual para a hora local
};

string SystemData::data() {
    struct tm *hl = SystemData::horarioLocal();

    return  to_string(hl->tm_year + 1900) + "-" + to_string(hl->tm_mon + 1) + "-" + to_string(hl->tm_mday);
}

string SystemData::hora() {
    struct tm *hl = SystemData::horarioLocal();

    return  to_string(hl->tm_hour)+ ":" + to_string(hl->tm_min) + ":" + to_string(hl->tm_sec) ;
}

string SystemData::dataHora() {
    return data()+"-"+hora();
}

string SystemData::horaData() {
    return hora()+"-"+data();
}

SystemData::~SystemData() {

}

SystemData::SystemData() {}
