#pragma once
#ifndef SPIFFSS_H
#define SPIFFSS_H

#include "esp_spiffs.h"
#include "esp_log.h"
#include <fstream>
#include <iostream>

namespace Spiffss
{
    esp_err_t SpiffssInit(void);
} // namespace Spiffs
#endif