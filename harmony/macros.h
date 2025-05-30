#pragma once

#define KILOBYTES(X) X * 1024ULL
#define MEGABYTES(X) X * 1024ULL * 1024ULL
#define GIGABYTES(X) X * 1024ULL * 1024ULL * 1024ULL

#define NORMAL_PRINT_CODE "\x1B[0m"
#define RED_PRINT_CODE "\x1B[31m"
#define GREEN_PRINT_CODE "\x1B[32m"
#define YELLOW_PRINT_CODE "\x1B[33m"
#define BLUE_PRINT_CODE "\x1B[34m"
#define MAGENTA_PRINT_CODE "\x1B[35m"
#define CYAN_PRINT_CODE "\x1B[36m"
#define WHITE_PRINT_CODE "\x1B[37m"

#include "SDL3/SDL_assert.h"
#define HNY_ASSERT(cond, message) SDL_assert(cond &&message)
#define HNY_ASSERT_NOT_REACHED() HNY_ASSERT(false, "Should not be reached")

#include <cstdio>
#define LOGGING_ENABLED
#ifdef LOGGING_ENABLED
#define HNY_LOG_INFO(msg, ...)                                                 \
  printf(BLUE_PRINT_CODE "[harmony][info ] " NORMAL_PRINT_CODE msg, __VA_ARGS__)
#define HNY_LOG_WARN(msg, ...)                                                 \
  printf(YELLOW_PRINT_CODE "[harmony][warn ] " NORMAL_PRINT_CODE msg,          \
         __VA_ARGS__)
#define HNY_LOG_ERROR(msg, ...)                                                \
  printf(RED_PRINT_CODE "[harmony][error] " NORMAL_PRINT_CODE msg, __VA_ARGS__)
#define HNY_LOG_DEBUG(msg, ...)                                                \
  printf(MAGENTA_PRINT_CODE "[harmony][debug] " NORMAL_PRINT_CODE msg,         \
         __VA_ARGS__)
#define HNY_LOG_TRACE(msg, ...)                                                \
  printf(CYAN_PRINT_CODE "[harmony][trace] " NORMAL_PRINT_CODE msg, __VA_ARGS__)
#else
#define HNY_LOG_INFO(msg, ...)
#define HNY_LOG_WARN(msg, ...)
#define HNY_LOG_ERROR(msg, ...)
#define HNY_LOG_DEBUG(msg, ...)
#define HNY_LOG_TRACE(msg, ...)
#endif