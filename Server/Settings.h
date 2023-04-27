#pragma once

#define HTTP_PORT 8080
#define SERVER_THREADS 16
#define USE_SERVER
#define USE_UI

#define DEFAULT_CONFIG_NAME "Config.json"


#define APP_NAME "SmartShop Server"

// Defines if nodes will automatically be allowed in
#define DEFAULT_AUTH true

// Disables the built in telemetry agent for the Server, define to turn off
#undef DISABLE_TELEMETRY_AGENT

#define INSTALLDIR "/usr/local/SmartShop"