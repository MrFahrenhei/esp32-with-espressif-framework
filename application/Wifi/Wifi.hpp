#pragma once
#include "esp_err.h"
#include "esp_wifi.h"
#include "esp_mac.h"
#include "esp_system.h"
#include <atomic>
namespace WIFI{
    class Wifi{
        public:
            enum class state_e
            {
                NOT_INITIALISED,
                INITIALISED,
                WAITING_FOR_CREDENTIALS,
                READY_TO_CONNECT,
                CONNECTING,
                WAITING_FOR_IP,
                CONNECTED,
                DISCONNECTED,
                ERROR,
            };
            Wifi(void)
            {
                static bool first_call = false;
                if(!first_call)
                {
                    if(ESP_OK != _get_mac()) esp_restart();
                    first_call = true;
                }
            }
            esp_err_t init(void); // set everything up
            esp_err_t begin(void); // start wifi, connect, etc
                                   //
            state_e get_state(void);
            const char* get_mac(void){ return mac_add_cstr; }
        private:
            void state_machine(void);

            esp_err_t _get_mac(void);
            static char mac_add_cstr[13];

            static std::atomic_bool first_call;

    };
} // namespace WIFI
