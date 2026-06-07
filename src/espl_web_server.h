#ifndef ESPL_WEB_SERVER_H
#define ESPL_WEB_SERVER_H
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "espl_config.h"
#include "espl_network.h"
#include "system_service.h"
#include "ws_data.h"
class EsplWebServer {
public:
    EsplWebServer(EsplConfig& config, EsplNetwork& network, SystemService& systemService);
    ~EsplWebServer();
    void begin();   
private:
    EsplConfig& config;
    EsplNetwork &network;
    AsyncWebServer *server;
    AsyncWebSocket *webSocket;
    SystemService *systemService;

    void setupRoutes();
    void setupWebSocket();
   
};
#endif // ESPL_WEB_SERVER_H