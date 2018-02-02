# Projeto Descontinuado.
# O novo projeto pode ser encontrado em:

 https://github.com/Eduardobalan/MonitorWeb-api 
 https://github.com/Eduardobalan/MonitorWeb-cli 

--------------------------------------------------------------


A documentação completa deste projeto pode ser encontrado em https://github.com/Eduardobalan/TCC-monitorWeb-Doc-Latex/blob/master/tcc.pdf

# TCC-monitorWeb

Sistema para monitoramento de servidores Linux, utilizando a arquitetura cliente-servidor. O sistema consiste em duas aplicações, um web service desenvolvido em Java para o qual foi dado o nome de MonitorWeb-Api(https://github.com/Eduardobalan/TCC-monitorWeb-api), e outra aplicação em C++(https://github.com/Eduardobalan/TCC-monitorWeb-Cliente), executada nos servidores Linux como cliente, tendo o nome de MonitorWeb-Cli.

# TCC-monitorWeb-Cli

O MonitorWeb-Cli realiza a leitura dos dados de seu hospedeiro, tais como CPU (Central Processing Unit), memória, banco de dados e swap. Esse procedimento é realizado de acordo com a configuração de tempo desejada pelo usuário. Para cada leitura realizada, o sistema realiza o envio dos dados para o MonitorWeb-Api. Ele também pode realizar rotinas de backups (cópia de segurança) e vaccum (processo de limpeza no banco de dados) do banco de dados PostgreSQL, tanto no hospedeiro quanto em outro computador a qual tenha acesso pela rede. Após efetuar esses procedimentos, o MonitorWeb-Cli envia mensagens para o MonitorWeb-Api que por sua vez armazena essas informações.

# TCC-monitorWeb-api

Um MonitorWeb-Api é responsável por receber os dados de diversos MonitorWeb-Cli e realizar a persistência no banco de dados. Também é responsável por armazenar as configurações dos clientes, tais como o intervalo de envio dos dados de monitoramento e as informações dos procedimentos de backup. Essas configurações são capturadas periodicamente conforme as configurações do usuário. A API também pode ser utilizada para disponibilizar os dados dos servidores para aplicações de front-end (aplicações responsáveis por coletar a entrada do usuário e processá-la para adequá-la a uma especificação em que o back-end possa utilizar).
