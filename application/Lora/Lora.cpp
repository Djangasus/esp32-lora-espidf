#include "Lora.h"

namespace Lora
{
    void loraSetConfig(Uart::UartTxRx esp32_uart, std::string TXRX_option)
    {
        std::vector<std::string> lora_setup = 
        {
            "at+set_config=device:restart\r\n",
            "at+set_config=device:uart_mode:1:1\r\n",
            "at+set_config=device:uart:1:115200\r\n",
            "at+set_config=lora:work_mode:1\r\n",
            "at+set_config=lorap2p:915000000:12:2:4:5:5\r\n",
            "at+set_config=lorap2p:transfer_mode:2\r\n",
            "at+set_config=device:uart_mode:1:1\r\n"
        };

        lora_setup[5] = (TXRX_option == "RX") ? "at+set_config=lorap2p:transfer_mode:1\r\n" : lora_setup[5];

        for (const std::string& message : lora_setup) {
            esp32_uart.send(message.c_str());
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    void sendBandsData(Uart::UartTxRx esp32_uart)
    {
        std::string data_filename = "/spiffs/data_rds.txt";

        std::ifstream inputFile(data_filename);
        std::string lora_band, lora_payload;
        if (inputFile.is_open())
        {
            ESP_LOGI(_log_tag, "INIT FILE");
            while (std::getline(inputFile, lora_band))
            {
                lora_payload = "at+send=lorap2p:" + lora_band + "\r\n";
                esp32_uart.send(lora_payload.c_str());

                vTaskDelay(480 / portTICK_PERIOD_MS);
                ESP_LOGI("TX", "%s: %s", std::to_string(getTimeUS()).c_str(), lora_band.c_str());
                // esp32_uart.receive();
            }
            inputFile.close();
            ESP_LOGI(_log_tag, "FILE SENT");
        }
        else
        {
            ESP_LOGW(_log_tag, "Failed to open Hexadecimal Data file");
        }
    }

    void readBandsData(Uart::UartTxRx esp32_uart)
    {
        uint8_t receivedData[65];
        size_t receivedLength = 0;
        
        ESP_ERROR_CHECK(esp32_uart.read(receivedData, &receivedLength));
        ESP_LOGI("RX", "%s: %s", std::to_string(getTimeUS()).c_str(), receivedData);

        memset(receivedData, 0, sizeof(receivedData));
        vTaskDelay(240 / portTICK_PERIOD_MS);
    }


    int64_t getTimeUS(void)
    {
        struct timeval tv_now;
        gettimeofday(&tv_now, NULL);
        return (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;
    }
}