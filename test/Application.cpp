#include "Application.hpp"
#include "IApplication.hpp"
#include <gtest/gtest.h>

// 示例测试：验证基础逻辑
TEST(ExampleTest, BasicAssertions) {
  EXPECT_EQ(2 + 2, 4); // 简单数学测试
  EXPECT_STRNE("hello", "world");
}

// 测试项目中某个类（假设Application类）
class ApplicationTest : public ::testing::Test {
protected:
  void SetUp() override {
    // 初始化代码（如果需要）
  }

  void TearDown() override {
    // 清理代码（如果需要）
  }
};

// TEST_F(ApplicationTest, TestGreeting) {
//   Application Application("Hello, World!"); // Provide constructor argument
//   EXPECT_EQ(Application.greet(), "Hello, World!");
// }
