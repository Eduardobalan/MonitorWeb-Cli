//
// Created by eduardo on 18/11/17.
//

#include "Resource.h"
#include "../SystemLog.h"
#include <iostream>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;

Resource::Resource(const string &path, const string &host = "127.0.0.1", unsigned short port = 80) : host(host), port(port), path(path) {
    setHost(host);
    setPort(port);
    setPath(path);
}
Result* Resource::get(){
    return exec("", "GET");
}
Result* Resource::post(const string &json){
    return exec(json, "POST");
}
Result* Resource::exec(const string &json, const string &verbo){
    try
    {
        if(!validarResource(verbo)){
            return new Result(0, "","Erro na validação dos dados ", verbo ,getPath(), getHost(), getPort(), json);
        };

        boost::asio::io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(host, std::to_string(port));
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.

        boost::asio::streambuf request;
        std::ostream request_stream(&request);

        if(verbo == "GET") {
            request_stream << "GET " << path << " HTTP/1.0\r\n";
            request_stream << "Host: " << host << "\r\n";
            request_stream << "Accept: */*\r\n";
            request_stream << "Connection: close\r\n\r\n";

        }else if (verbo == "POST") {
            request_stream << "POST " << path << " HTTP/1.0\r\n";
            request_stream << "Host: " << host << "\r\n";
            request_stream << "Accept: */*\r\n";
            request_stream << "Content-Length: " << json.length() << "\r\n";
            request_stream << "Content-Type: application/json;charset=UTF-8\r\n";
            request_stream << "Connection: close\r\n\r\n";
            request_stream << json;
        }else{
            return new Result(0, "","Verbo deve ser POST ou GET!",verbo, getPath(), getHost(), getPort(), json);
        }

        // Send the request.
        boost::asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            return new Result(400, "", "Invalid response!", verbo, getPath(), getHost(), getPort(), json);
        }
        if (status_code != 200)
        {
            return new Result(status_code, "", "Response returned with status code!", verbo, getPath(), getHost(), getPort(), json);
        }

        // Read the response headers, which are terminated by a blank line.
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Process the response headers.
        std::string header;
        while (std::getline(response_stream, header) && header != "\r"){

        }
//            std::cout << header << "\n";
//        std::cout << "\n";
//
//         Write whatever content we already have to output.
//        if (response.size() > 0)
//            std::cout << &response;
//
        //Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)){
        }
        std::ostringstream ss;
        std::string s;
        ss << &response;
        s = ss.str();

        if (error != boost::asio::error::eof){
            throw boost::system::system_error(error);
        }else{
            return new Result(status_code, s, "", verbo, getPath(), getHost(), getPort(), json);
        }
    }
    catch (std::exception& e)
    {
        //std::cerr << "Post Exception:" << e.what() << endl;
        return new Result(0, "","Connection refused", verbo, getPath(), getHost(), getPort(), json);
    }
}



bool Resource::validarResource(const string &verbo) {
    if(verbo != "GET" && verbo != "POST"){
        SystemLog::execLog('e',": Resource: Verbo deve ser GET OU POST!: ");
        return false;
    }
    if (getPort() == 0)
    {
        SystemLog::execLog('e',": Resource: Porta não definida!: ");
        return false;
    }
    if (getHost().length() == 0)
    {
        SystemLog::execLog('e',": Resource: Host não definido!: ");
        return false;
    }
    if (getPath().length() == 0)
    {
        SystemLog::execLog('e',": Resource: Path não definido!: ");
        return false;
    }
    return true;
}

