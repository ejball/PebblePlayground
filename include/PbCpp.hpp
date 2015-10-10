#pragma once

#ifndef PBCPP_H
#define PBCPP_H

extern "C" {
  #define _NEWLIB_ALLOCA_H
  #include <pebble.h>
}

#include <algorithm>
#include <memory>
#include <new>

#define PB_LOG_ERROR(fmt, args...) app_log(APP_LOG_LEVEL_ERROR, __FILE_NAME__, __LINE__, fmt, ## args)
#define PB_LOG_WARNING(fmt, args...) app_log(APP_LOG_LEVEL_WARNING, __FILE_NAME__, __LINE__, fmt, ## args)
#define PB_LOG_INFO(fmt, args...) app_log(APP_LOG_LEVEL_INFO, __FILE_NAME__, __LINE__, fmt, ## args)
#define PB_LOG_DEBUG(fmt, args...) app_log(APP_LOG_LEVEL_DEBUG, __FILE_NAME__, __LINE__, fmt, ## args)
#define PB_LOG_VERBOSE(fmt, args...) app_log(APP_LOG_LEVEL_DEBUG_VERBOSE, __FILE_NAME__, __LINE__, fmt, ## args)

#define PB_CRASH() free((void *)1)
#define PB_ASSERT(X) do { if (!(X)) { PB_LOG_ERROR("Assertion failure!"); PB_CRASH(); } } while(false)

namespace PbCpp {
  #include "src/PbRect.hpp"
  #include "src/PbString.hpp"
  #include "src/PbTickTimer.hpp"
  #include "src/PbLayer.hpp"
  #include "src/PbWindow.hpp"
  #include "src/PbTextLayer.hpp"
  #include "src/PbApp.hpp"
}

#endif