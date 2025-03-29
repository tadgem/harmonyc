#include "STL.h"

namespace harmony {
str_hash HashString(const String &input) {
  static auto hasher = eastl::string_hash<String>();
  return hasher(input);
}
} // namespace harmony
