#pragma once
#ifndef LORA_H
#define LORA_H

#include "esp_log.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

#include "../Uart/Uart.h"

namespace Lora
{
    constexpr static const char* _log_tag{"STATUS"};

    void loraSetConfig(Uart::UartTxRx esp32_uart, std::string TXRX_option);
    void sendBandsData(Uart::UartTxRx esp32_uart);
    void readBandsData(Uart::UartTxRx esp32_uart);
    int64_t getTimeUS(void);
} // namespace Lora
#endif