#pragma once

#define KILOBYTES(X) X * 1024ULL
#define MEGABYTES(X) X * 1024ULL * 1024ULL
#define GIGABYTES(X) X * 1024ULL * 1024ULL * 1024ULL

#include "SDL3/SDL_assert.h"
#define HNY_ASSERT(cond, message) SDL_assert(cond && message)