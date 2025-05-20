#pragma once
#include "STL.h"

namespace harmony {
class Utils {
public:
  static Vector<char> LoadBinaryFromPath(const char *path);
};
} // namespace harmony