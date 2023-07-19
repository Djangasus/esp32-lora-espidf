#include "main.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE     // all log messages will be included in the compiled binary, regardless of their log level. 
#include "esp_log.h"
#define LOG_TAG "MAIN"  // log tag for main file messages.

const std::string TXRX_OPTION = "RX";

static Main mymain;

extern "C" void app_main(void)
{
    ESP_LOGI(LOG_TAG, "Creating default event loop");
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_LOGI(LOG_TAG, "Initializing NVS");
    ESP_ERROR_CHECK(nvs_flash_init());

    ESP_ERROR_CHECK(mymain.setup());

    while(true)
    {
        mymain.loop();
    }
}

esp_err_t Main::setup(void)
{
    esp_err_t status{ESP_OK};

    status |= Spiffss::SpiffssInit();
    status |= esp32_uart.init();
    status |= wifi.init();

    if (ESP_OK == status) status |= wifi.begin();
    wifi.startSNTP();
    ESP_LOGI(LOG_TAG, "SNTP - synchronized internal clock");
    ESP_LOGI(LOG_TAG, "Setup completed!");

    return status;
}

void Main::loop(void)
{
    if (TXRX_OPTION == "TX")
    {
        Lora::sendBandsData(esp32_uart);
    }
    else
    {
        Lora::readBandsData(esp32_uart);
    }
}