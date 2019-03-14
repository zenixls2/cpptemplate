#include <gtest/gtest.h>

class Test: public testing::Test {
protected:
    Test() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(Test, test_basic) {
    ASSERT_EQ(1, 1);
}
