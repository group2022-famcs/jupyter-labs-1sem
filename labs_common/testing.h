#pragma once
#pragma cling add_library_path("gtest")

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "assert.h"

#undef G_ASSERT_
#define G_ASSERT_(expression) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const ::testing::AssertionResult gtest_ar = (expression)) \
    std::cerr << "OK"; \
  else \
    throw std::runtime_error(gtest_ar.failure_message());

#undef ASSERT_THAT
#define ASSERT_THAT(value, matcher) G_ASSERT_(::testing::internal::MakePredicateFormatterFromMatcher(matcher)(#value, value));
