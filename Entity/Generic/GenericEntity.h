//
// Created by eduardo on 03/10/17.
//

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#ifndef WEBMONITOR_CLIENTE_GENERICENTITY_H
#define WEBMONITOR_CLIENTE_GENERICENTITY_H

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::string;
using std::cout;


class GenericEntity {

private:

public:
    virtual bool fromJson(const string &json) = 0;

    virtual string toJson() = 0;


};


#endif //WEBMONITOR_CLIENTE_GENERICENTITY_H
