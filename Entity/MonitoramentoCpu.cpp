//
// Created by eduardo on 14/09/17.
//

#include "MonitoramentoCpu.h"

using namespace std;

MonitoramentoCpu::MonitoramentoCpu() {}

MonitoramentoCpu::~MonitoramentoCpu() {}


std::string MonitoramentoCpu::toJson(){
    // Write json.
    ptree pt;
    pt.put ("numeroNucleos", getNumeroNucleos());
    pt.put ("cpuMhz", getCpuMhz());

    std::ostringstream buf;
    write_json (buf, pt, false);
    string json = buf.str();
    return  json;
}

bool MonitoramentoCpu::fromJson(const std::string &json){
    // Read json.
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);

    setNumeroNucleos(pt2.get<long> ("numeroNucleos"));
    setCpuMhz(pt2.get<long> ("cpuMhz"));

    return true;
}
void MonitoramentoCpu::print() {
    //if() {
    cout << "---------MonitoramentoCpu-------------" << endl;
    cout << "numeroNucleos: " << getNumeroNucleos() << endl;
    cout << "cpuMhz: " << getCpuMhz() << endl;
    cout << "-------------------------"<< endl;
    //}
}
