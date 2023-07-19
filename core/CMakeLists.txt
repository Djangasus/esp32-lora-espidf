set(SOURCES ./Src/main.cpp)

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS . Inc
                    REQUIRES freertos esp_common esp_event nvs_flash Uart Spiffss Lora Wifi)

spiffs_create_partition_image(storage ../spiffs_data FLASH_IN_PROJECT)