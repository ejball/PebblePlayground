#pragma once

#ifndef PBCPP_H
#define PBCPP_H

extern "C" {
#define _NEWLIB_ALLOCA_H
#include <pebble.h>
}

#include <algorithm>

#define ASSERT(X) do { if (!(X)) { APP_LOG(APP_LOG_LEVEL_ERROR, "Assertion failure!"); free((void *)1); } } while(false)

namespace PbCpp {

#include "src/PbString.hpp"
#include "src/PbTickTimer.hpp"
#include "src/PbLayer.hpp"
#include "src/PbWindow.hpp"
#include "src/PbTextLayer.hpp"
#include "src/PbApp.hpp"

}

#endif
