#pragma once
#include <cstdint>

inline int32_t round_up(int32_t value, int32_t alignment) {
  return ((value - 1) | (alignment - 1)) + 1;
}
