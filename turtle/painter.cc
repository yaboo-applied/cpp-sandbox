#include "turtle/turtle.h"
#include "turtle/painter.h"

Painter::Painter(Turtle* turtle) { turtle_ = turtle; }

bool Painter::DrawCircle(int x, int y, int z) {
  turtle_->PenDown();
  return true;
}

void Painter::MultipleGetX(int num) {
  for (int i = 0; i < num; i++) {
    turtle_->GetX();
  }
}

void Painter::ForwardGoTo() {
  turtle_->Forward(10);
  turtle_->GoTo(10, 10);
}
