//
// Created by eduardo on 08/11/17.
//

#include "SystemData.h"

SystemData::~SystemData() {

}

SystemData::SystemData() {}

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

    string hour = hl->tm_hour >= 10 ? to_string(hl->tm_hour) : "0"+to_string(hl->tm_hour) ;
    string min  = hl->tm_min  >= 10 ? to_string(hl->tm_min)  : "0"+to_string(hl->tm_min) ;
    string sec  = hl->tm_sec  >= 10 ? to_string(hl->tm_sec)  : "0"+to_string(hl->tm_sec) ;

    return  hour+ ":" + min + ":" + sec;
}

string SystemData::dataHora() {
    return data()+"-"+hora();
}

string SystemData::horaData() {
    return hora()+"-"+data();
}
