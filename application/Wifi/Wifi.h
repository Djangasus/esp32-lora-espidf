#pragma once

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"

#include <algorithm>
#include <mutex>

#include <sys/time.h>
#include "esp_netif.h"
#include <esp_sntp.h>
#include <iostream>
#include <thread>
// #include <atomic>
// #include <stdatomic.h>

#include <cstring>

namespace WIFI
{
    class Wifi
    {
        constexpr static const char* _log_tag{"WiFi"};
        
        // constexpr static const char* _ssid{"Redmi Note 11"};
        // constexpr static const char* _password{"12345456789#"};

        constexpr static const char* _ssid{"INVITADOS_INICTEL"};
        constexpr static const char* _password{"1n1ctel_1nv1tados"};

        public:
            enum class state_e
            {
                NOT_INITIALIZED,
                INITIALIZED,
                WAITING_FOR_CREDENTIALS,
                READY_TO_CONNECT,
                CONNECTING,
                WAITING_FOR_IP,
                CONNECTED,
                DISCONNECTED,
                ERROR
            };

            // "Rule of five"
            Wifi(void);
            ~Wifi(void)                     = default;
            Wifi(const Wifi &)              = default;
            Wifi(Wifi&&)                    = default;
            Wifi& operator=(const Wifi&)    = default;
            Wifi& operator=(Wifi&&)         = default;

            esp_err_t init(void);   // Set everything up
            esp_err_t begin(void);  // Start wifi, connect, etc

            constexpr const state_e& get_state(void) 
                { return _state; }

            constexpr static const char* get_mac(void)
                { return mac_addr_cstr; }

            void startSNTP();

        private:
            static esp_err_t _init(void);
            static wifi_init_config_t wifi_init_config;
            static wifi_config_t wifi_config;

            void state_machine(void);

            static void event_handler(void* arg, esp_event_base_t event_base,
                                        int32_t event_id, void* event_data);
            static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                            int32_t event_id, void* event_data);
            static void ip_event_handler(void* arg, esp_event_base_t event_base,
                                            int32_t event_id, void* event_data);
            
            static state_e _state;
            
            static esp_err_t _get_mac(void);

            static char mac_addr_cstr[13];
            static std::mutex init_mutx;
            static std::mutex connect_mutx;
            static std::mutex state_mutx;
    };
}