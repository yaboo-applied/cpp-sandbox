#ifndef PAINTER_H
#define PAINTER_H

class Painter {
 public:
  Painter(Turtle* turtle);
  bool DrawCircle(int x, int y, int z);
  void MultipleGetX(int num);
  void ForwardGoTo();

 private:
  Turtle* turtle_;
};

#endif  /* PAINTER_H */