#include <gtest/gtest.h>

#include "math/Vector3D.h"

TEST(TestSuiteName, TestName)
{
  const auto result = app::math::add(1, 2);
  // EXPECT_GT(result, 0);
  EXPECT_EQ(2 + 2, 4);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}