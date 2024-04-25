// interface view

#ifndef MAZE_VIEW_VIEW_H_
#define MAZE_VIEW_VIEW_H_

namespace mc {

class View {
 public:
  View() {}
  virtual ~View() {}

  virtual int Exec() = 0;
};

}  // namespace mc

#endif  // MAZE_VIEW_VIEW_H_
