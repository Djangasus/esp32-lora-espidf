#pragma once
#ifndef UART_H
#define UART_H

#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

namespace Uart
{
    class UartBase
    {
        protected:
            const uart_port_t _u_port;
            const int _tx_io_num_fixed;
            const int _rx_io_num_fixed;
        
        public:
            constexpr UartBase( const uart_port_t u_port, 
                                const int tx_io_num_fixed, 
                                const int rx_io_num_fixed) : 
                _u_port{u_port},
                _tx_io_num_fixed{tx_io_num_fixed},
                _rx_io_num_fixed{rx_io_num_fixed}
            {

            }
    };

    class UartTxRx : public UartBase
    {
        public:
            constexpr UartTxRx( const uart_port_t u_port,
                                const int tx_io_num_fixed, 
                                const int rx_io_num_fixed) : 
                UartBase{u_port, tx_io_num_fixed, rx_io_num_fixed}
            {

            };
            
            [[nodiscard]] esp_err_t init(void);
            esp_err_t send(const char* data);
            esp_err_t read(uint8_t *data, size_t *lenx);
    };

} // namespace Uart
#endif