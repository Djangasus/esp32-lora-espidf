#include "Spiffss.h"

#define TAG "spiffs"

namespace Spiffss
{
    esp_err_t SpiffssInit(void)
    {
        ESP_LOGI(TAG, "Initializing SPIFFS");

        esp_vfs_spiffs_conf_t conf = {
            .base_path = "/spiffs",
            .partition_label = NULL,
            .max_files = 5,
            .format_if_mount_failed = true
        };

        // Use settings defined above to initialize and mount SPIFFS filesystem.
        // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
        esp_err_t ret = esp_vfs_spiffs_register(&conf);

        if (ret != ESP_OK) {
            if (ret == ESP_FAIL) {
                ESP_LOGE(TAG, "Failed to mount or format filesystem");
            } else if (ret == ESP_ERR_NOT_FOUND) {
                ESP_LOGE(TAG, "Failed to find SPIFFS partition");
            } else {
                ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
            }
            return ret;
        }

        #ifdef CONFIG_EXAMPLE_SPIFFS_CHECK_ON_START
            ESP_LOGI(TAG, "Performing SPIFFS_check().");
            ret = esp_spiffs_check(conf.partition_label);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
                return;
            } else {
                ESP_LOGI(TAG, "SPIFFS_check() successful");
            }
        #endif

        size_t total = 0, used = 0;
        ret = esp_spiffs_info(conf.partition_label, &total, &used);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s). Formatting...", esp_err_to_name(ret));
            esp_spiffs_format(conf.partition_label);
            return ret;
        } else {
            ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
        }

        return ret;
    }
}


