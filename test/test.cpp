#include <gtest/gtest.h>
#include "IGreeter.h"
#include "Greeter.h"  // Add this line to include the concrete implementation

// 示例测试：验证基础逻辑
TEST(ExampleTest, BasicAssertions) {
    EXPECT_EQ(2 + 2, 4);  // 简单数学测试
    EXPECT_STRNE("hello", "world");
}

// 测试项目中某个类（假设Greeter类）
class GreeterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 初始化代码（如果需要）
    }

    void TearDown() override {
        // 清理代码（如果需要）
    }
};

TEST_F(GreeterTest, TestGreeting) {
    Greeter greeter("Hello, World!");  // Provide constructor argument
    EXPECT_EQ(greeter.greet(), "Hello, World!");
}
