#include "Utils.h"
#include <fstream>
namespace harmony {
Vector<char> Utils::LoadBinaryFromPath(const char *path) {
  std::ifstream input(path, std::ios::binary);

  Vector<char> bytes;
  int iterations = 0;
  char c = 0;
  input.read(&c, 1);
  while (!input.eof()) {
    bytes.push_back(c);
    input.read(&c, 1);
    iterations++;
  }

  input.close();
  return bytes;
}
} // namespace harmony