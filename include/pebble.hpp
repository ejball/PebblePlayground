#pragma once

extern "C" {
#define _NEWLIB_ALLOCA_H
#include <pebble.h>
}

#include <algorithm>

#define ASSERT(X) do { if (!(X)) { APP_LOG(APP_LOG_LEVEL_ERROR, "Assertion failure!"); free((void *)1); } } while(false)

#include "headers/PebbleString.hpp"
#include "headers/PebbleTickTimer.hpp"
#include "headers/PebbleLayer.hpp"
#include "headers/PebbleWindow.hpp"
#include "headers/PebbleTextLayer.hpp"
#include "headers/PebbleApp.hpp"
