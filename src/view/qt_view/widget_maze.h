// widget maze

#ifndef MAZE_VIEW_WIDGET_MAZE_H_
#define MAZE_VIEW_WIDGET_MAZE_H_

#include <QColor>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <cstddef>
#include <vector>

#include "matrix.h"

namespace mc {

class WidgetMaze : public QWidget {
  Q_OBJECT

 public:
  struct Point {
    int x;
    int y;
  };

  WidgetMaze(QWidget *parent = nullptr);
  virtual ~WidgetMaze();

  void SetMazeWidth(size_t maze_width);
  void SetMazeHeight(size_t maze_height);
  void SetVerticalWall(mtlc::Matrix<bool> vertical_wall);
  void SetHorisontalWall(mtlc::Matrix<bool> horisontal_wall);
  void SetNeedSolution(bool need_solution);
  void SetSolution(std::vector<Point> sol);
  void SetStartSelected(bool start_selected);
  void SetEndSelected(bool end_selected);
  void SetStartIdx(size_t start_idx_x, size_t start_idx_y);
  void SetEndIdx(size_t end_idx_x, size_t end_idx_y_);

 signals:
  void SignalStartSelected(size_t start_idx_x, size_t start_idx_y);
  void SignalEndSelected(size_t end_idx_x, size_t end_idx_y_);

 private:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

  void DrawStart(QPainter *painter, int x, int y, int w, int h);
  void DrawEnd(QPainter *painter, int x, int y, int w, int h);
  void DrawVerticalWall(QPainter *painter, int x, int y, int size);
  void DrawHorisontalWall(QPainter *painter, int x, int y, int size);

  static const QColor kColorCell_;
  static const QColor kColorWall_;
  static const QColor kColorWay_;

  static const int kWidthWall_;

  size_t maze_width_;
  size_t maze_height_;
  mtlc::Matrix<bool> vertical_wall_;
  mtlc::Matrix<bool> horisontal_wall_;

  bool need_solution_;
  std::vector<Point> solution_;

  bool start_selected_;
  bool end_selected_;
  size_t start_idx_x_;
  size_t start_idx_y_;
  size_t end_idx_x_;
  size_t end_idx_y_;
};

}  // namespace mc

#endif  // MAZE_VIEW_WIDGET_MAZE_H_
