//
// Created by eduardo on 08/11/17.
//

#ifndef WEBMONITOR_CLIENTE_SYSTEMDATA_H
#define WEBMONITOR_CLIENTE_SYSTEMDATA_H


#include <ctime>
#include <string>
#include <iostream>

using namespace std;

class SystemData {
private:
    static struct tm* horarioLocal();
public:
    SystemData();

    virtual ~SystemData();

    static string dataHora();

    static string horaData();

    static string hora();

    static string data();

};


#endif //WEBMONITOR_CLIENTE_SYSTEMDATA_H
