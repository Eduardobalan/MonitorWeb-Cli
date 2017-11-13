cmake_minimum_required(VERSION 3.8)
project(WebMonitor_Cliente)

set(CMAKE_CXX_STANDARD 11)

set(BOOST_ROOT "/usr/local/boost_1_65_1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lboost_system -lboost_thread")
find_package(Boost 1.65.1)
if(Boost_FOUND)
    include_directories("/usr/local/boost_1_65_1")
endif()


set(SOURCE_FILES main.cpp Entity/Servidor.cpp Entity/Servidor.h Entity/InformacoesCpu.cpp Entity/InformacoesCpu.h Entity/MonitoramentoCpu.cpp Entity/MonitoramentoCpu.h main.cpp Entity/Generic/GenericEntity.cpp Entity/Generic/GenericEntity.h  Util/verbosHttp/Get.cpp Util/verbosHttp/Get.h Util/verbosHttp/Result.cpp Util/verbosHttp/Result.h Entity/ServidorConfig.cpp Entity/ServidorConfig.h Util/verbosHttp/Post.cpp Util/verbosHttp/Post.h  Util/ConfigFile/ConfigFile.cpp Util/ConfigFile/ConfigFile.h Util/ConfigFile/Exceptions.h Util/SystemLog.cpp Util/SystemLog.h Entity/InformacoesMemoria.cpp Entity/InformacoesMemoria.h Entity/MonitoramentoMemoria.cpp Entity/MonitoramentoMemoria.h Entity/InformacoesSwap.cpp Entity/InformacoesSwap.h Entity/MonitoramentoSwap.cpp Entity/MonitoramentoSwap.h Entity/MonitoramentoPostgresInformacoes.cpp Entity/MonitoramentoPostgresInformacoes.h Entity/MonitoramentoPostgres.cpp Entity/MonitoramentoPostgres.h Entity/ServidorConfigDb.cpp Entity/ServidorConfigDb.h Util/SystemData.cpp Util/SystemData.h Entity/ThreadLerServidorConfigDb.cpp Entity/ThreadLerServidorConfigDb.h Entity/ThreadLerServidorConfigInformacoesDb.cpp Entity/ThreadLerServidorConfigInformacoesDb.h Entity/ServidorConfigInformacoesDb.cpp Entity/ServidorConfigInformacoesDb.h)
add_executable(WebMonitor_Cliente ${SOURCE_FILES} Entity/Servidor.h Entity/Servidor.cpp Entity/InformacoesCpu.cpp Entity/InformacoesCpu.h Entity/InformacoesMemoria.cpp Entity/InformacoesMemoria.h Entity/MonitoramentoMemoria.cpp Entity/MonitoramentoMemoria.h Entity/InformacoesSwap.cpp Entity/InformacoesSwap.h Entity/MonitoramentoSwap.cpp Entity/MonitoramentoSwap.h Entity/MonitoramentoPostgresInformacoes.cpp Entity/MonitoramentoPostgresInformacoes.h Entity/MonitoramentoPostgres.cpp Entity/MonitoramentoPostgres.h Entity/ServidorConfigDb.cpp Entity/ServidorConfigDb.h Entity/ThreadLerServidorConfigDb.cpp Entity/ThreadLerServidorConfigDb.h Entity/ThreadLerServidorConfigInformacoesDb.cpp Entity/ThreadLerServidorConfigInformacoesDb.h Entity/ServidorConfigInformacoesDb.cpp Entity/ServidorConfigInformacoesDb.h)
