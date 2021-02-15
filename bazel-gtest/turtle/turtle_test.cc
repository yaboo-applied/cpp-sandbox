#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "turtle/mock_turtle.h"
#include "turtle/painter.h"

using ::testing::AtLeast;                         // #1

TEST(PainterTest, CanDrawSomething) {
  MockTurtle turtle;                              // #2
  EXPECT_CALL(turtle, PenDown())                  // #3
      .Times(AtLeast(1));

  Painter painter(&turtle);                       // #4

  EXPECT_TRUE(painter.DrawCircle(0, 0, 10));      // #5
}

TEST(PainterTest, CanCallMultipleGetX) {
  MockTurtle turtle;
  EXPECT_CALL(turtle, GetX()).Times(5);
  Painter painter(&turtle);
  painter.MultipleGetX(5);
}

TEST(PainterTest, CanForwardGoTo) {
  MockTurtle turtle;
  // Expects the turtle to move forward.
  EXPECT_CALL(turtle, Forward);
  // Expects the turtle to jump somewhere.
  EXPECT_CALL(turtle, GoTo);
  Painter painter(&turtle);
  painter.ForwardGoTo();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
