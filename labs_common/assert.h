#pragma once

#include <stdexcept>

#undef ASSERT
#define ASSERT(cond) if (!(cond)) { throw std::runtime_error("Assertion failed: " #cond); }
