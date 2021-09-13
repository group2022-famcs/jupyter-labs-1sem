#pragma once

#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(cond) if (!(cond)) { throw std::runtime_error("Assertion failed: " #cond); }
