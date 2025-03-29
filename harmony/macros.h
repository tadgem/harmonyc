#pragma once

#define KILOBYTES(X) X * 1024ULL
#define MEGABYTES(X) X * 1024ULL * 1024ULL
#define GIGABYTES(X) X * 1024ULL * 1024ULL * 1024ULL

#include "SDL3/SDL_assert.h"
#define HNY_ASSERT(cond, message) SDL_assert(cond &&message)
#define HNY_ASSERT_NOT_REACHED() HNY_ASSERT(false, "Should not be reached")

#include "SDL3/SDL_log.h"
#define HNY_LOG_TRACE(msg,...) SDL_LogTrace(0, msg, __VA_ARGS__)
#define HNY_LOG_INFO(msg,...) SDL_LogInfo(0, msg, __VA_ARGS__)
#define HNY_LOG_WARN(msg,...) SDL_LogWarn(0, msg, __VA_ARGS__)
#define HNY_LOG_DEBUG(msg,...) SDL_LogDebug(0, msg, __VA_ARGS__)
#define HNY_LOG_ERROR(msg,...) SDL_LogError(0, msg, __VA_ARGS__)