#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include "Uart.h"
#include "Spiffss.h"
#include "Lora.h"
#include "Wifi.h"

class Main final
{
    public:
        esp_err_t setup(void);
        void loop(void);

        Uart::UartTxRx esp32_uart{UART_NUM_2, 17, 16};

        WIFI::Wifi wifi;
};