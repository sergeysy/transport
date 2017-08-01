#include <gtest/gtest.h>
#include "settings.hpp"
#include "transport.hpp"

/*int add(int value1, int value2) {
  return (value1 + value2);
}

TEST (AddTest, PositiveNos) {
  EXPECT_EQ (16, add(8, 8));
}*/
int main(int argc, char *argv[])
//int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}