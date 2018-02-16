
# Índice de conteúdo

* [Introdução MonitorWeb](#introdução "Introdução sobre o sistema MonitorWeb")
  * [Introdução MonitorWeb-Cli](#monitorweb-cli "Introdução sobre o sistema MonitorWeb-Cli")
  * [Introdução MonitorWeb-Api](#monitorweb-api "Introdução sobre o sistema MonitorWeb-Api")
* [Guia de instalação](#guia-de-instalação "Guia de instalação")
   * [Aplicação](#aplicação "Aplicação")
   * [Teste com Valgrind](#teste-com-valgrind "Teste com Valgrind")
* [Notas de release](#notas-de-release "Notas de release do projeto")
* [Issues](#issues "Issues do projeto")


## Introdução

Sistema para monitoramento de servidores Linux, utilizando a arquitetura cliente-servidor. O sistema consiste em duas aplicações, um web service desenvolvido em Java para o qual foi dado o nome de MonitorWeb-Api(https://github.com/Eduardobalan/monitorWeb-api), e outra aplicação em C++(https://github.com/Eduardobalan/monitorWeb-Cli), executada nos servidores Linux como cliente, tendo o nome de MonitorWeb-Cli.

### MonitorWeb-Cli

O MonitorWeb-Cli realiza a leitura dos dados de seu hospedeiro, tais como CPU (Central Processing Unit), memória, banco de dados e swap. Esse procedimento é realizado de acordo com a configuração de tempo desejada pelo usuário. Para cada leitura realizada, o sistema realiza o envio dos dados para o MonitorWeb-Api. Ele também pode realizar rotinas de backups (cópia de segurança) e vaccum (processo de limpeza no banco de dados) do banco de dados PostgreSQL, tanto no hospedeiro quanto em outro computador a qual tenha acesso pela rede. Após efetuar esses procedimentos, o MonitorWeb-Cli envia mensagens para o MonitorWeb-Api que por sua vez armazena essas informações.

### MonitorWeb-Api

Um MonitorWeb-Api é responsável por receber os dados de diversos MonitorWeb-Cli e realizar a persistência no banco de dados. Também é responsável por armazenar as configurações dos clientes, tais como o intervalo de envio dos dados de monitoramento e as informações dos procedimentos de backup. Essas configurações são capturadas periodicamente conforme as configurações do usuário. A API também pode ser utilizada para disponibilizar os dados dos servidores para aplicações de front-end (aplicações responsáveis por coletar a entrada do usuário e processá-la para adequá-la a uma especificação em que o back-end possa utilizar).


## Guia de Instalação

### Aplicação
- A aplicação depende de duas instalações `libboost-all-dev` e `boost`. A versão da biblioteca boost utilizada no desenvolvimento foi a 1.65.1, caso ocorra erro na execução de outra versão baixe manualmente e ajuste o arquivo CMakeLists.txt na rais do projeto.  

      `sudo apt-get install libboost-all-dev`
      
      `sudo apt-get install boost`

### Teste com Valgrind
 Deve ser instalado o Valgrid:
 
      `sudo apt-get install valgrind`
      
 Para rodar o teste use os comando abaixo no diretorio de compilaçõa do seu projeto.
    
      `valgrind ./WebMonitor_Cliente`
      
      `valgrind --leak-check=yes ./WebMonitor_Cliente`


-----

## Notas de release

Para visualizar as notas de release acesse o _link_ abaixo:

[Notas de release](CHANGELOG.md)

-----

## Issues

Veja os issues do projeto: [aqui](../../issues)