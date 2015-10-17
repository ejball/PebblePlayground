#pragma once

#ifndef PBCPP_H
#define PBCPP_H

extern "C" {
  #define _NEWLIB_ALLOCA_H
  #include <pebble.h>
  #undef open
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

namespace pbcpp {
  #include "src/PbNoncopyable.h"
  #include "src/PbDateTimeInfo.h"
  #include "src/PbDateTime.h"
  #include "src/PbRect.h"
  #include "src/PbString.h"
  #include "src/PbHandleRef.h"
  #include "src/PbFontRef.h"
  #include "src/PbCustomFont.h"
  #include "src/PbBitmapRef.h"
  #include "src/PbBitmap.h"
  #include "src/PbLayerRef.h"
  #include "src/PbHasLayer.h"
  #include "src/PbClickRecognizerRef.h"
  #include "src/PbWindowRef.h"
  #include "src/PbWindow.h"
  #include "src/PbBitmapLayer.h"
  #include "src/PbTextLayerRef.h"
  #include "src/PbTextLayer.h"
  #include "src/PbTickTimer.h"
  #include "src/PbTupleRef.h"
  #include "src/PbDictionaryIteratorRef.h"
  #include "src/PbDictionaryReader.h"
  #include "src/PbAppMessages.h"
  #include "src/PbMain.h"
}

#endif
