#include "Uart.h"
#include <cstring>

#define BUFFER_SIZEE 65     // fixed for Radio Data System frame length

namespace Uart
{
    [[nodiscard]] esp_err_t UartTxRx::init(void)
    {
        // Initialize uart config structure
        uart_config_t uart_cfg = {
                                .baud_rate              = 115200,
                                .data_bits              = UART_DATA_8_BITS,
                                .parity                 = UART_PARITY_DISABLE,
                                .stop_bits              = UART_STOP_BITS_1,
                                .flow_ctrl              = UART_HW_FLOWCTRL_DISABLE,
                                .rx_flow_ctrl_thresh    = 122,
                                .source_clk             = UART_SCLK_APB
                            };

         // Set UART parameters
        ESP_ERROR_CHECK(uart_param_config(_u_port, &uart_cfg));

        // Set UART TX and RX pins
        ESP_ERROR_CHECK(uart_set_pin(_u_port, _tx_io_num_fixed, _rx_io_num_fixed, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

        // Driver installation
        const int tx_uart_buffer_size = (BUFFER_SIZEE * 2);
        const int rx_uart_buffer_size = (BUFFER_SIZEE * 2);
        ESP_ERROR_CHECK(uart_driver_install(_u_port, rx_uart_buffer_size, tx_uart_buffer_size, 0, NULL, 0));

        return ESP_OK;
    };

    esp_err_t UartTxRx::send(const char* u_data)
    {
        return uart_write_bytes(_u_port, u_data, strlen(u_data));
    };

    esp_err_t UartTxRx::read(uint8_t *data, size_t *lenx)
    {
        //ESP_ERROR_CHECK(uart_get_buffered_data_len(_u_port, (size_t*)&lenx));
        *lenx = uart_read_bytes(_u_port, data, BUFFER_SIZEE, 0);
        // vTaskDelay(1);
        return ESP_OK;
    };

} // namespace Uart