#pragma once

#include "cling_common.hpp"

#include <cstdint>

namespace www
{
namespace zzz
{

enum class
$apply(
  reflect_enum
)
ReflShapeKind0 : uint32_t {
  Box = 3,
  Sphere = 6,
};

enum
$apply(
  reflect_enum
)
ReflShapeKind2 {
  Box,
  Sphere,
};

} // namespace zzz
} // namespace www
