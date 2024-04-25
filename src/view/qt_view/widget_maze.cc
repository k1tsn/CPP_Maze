// widget maze

#include "widget_maze.h"

#include <QColor>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <cstddef>
#include <vector>

#include "matrix.h"

namespace mc {

WidgetMaze::WidgetMaze(QWidget *parent) : QWidget(parent) {
  maze_width_ = 1;
  maze_height_ = 1;
  vertical_wall_ = mtlc::Matrix<bool>(1, 1);
  horisontal_wall_ = mtlc::Matrix<bool>(1, 1);
  vertical_wall_(0, 0) = true;
  horisontal_wall_(0, 0) = true;
  need_solution_ = false;
  start_selected_ = false;
  end_selected_ = false;
}

WidgetMaze::~WidgetMaze() {}

void WidgetMaze::paintEvent(QPaintEvent *event) {
  if (maze_height_ == 0 || maze_width_ == 0) return;

  event->accept();
  QPainter painter(this);

  painter.fillRect(0, 0, width(), height(), kColorCell_);
  int cell_width = width() / maze_width_;
  int cell_width_off = (width() - cell_width * maze_width_) / 2;
  int cell_height = height() / maze_height_;
  int cell_height_off = (height() - cell_height * maze_height_) / 2;

  if (start_selected_) {
    int x = cell_width_off + cell_width * start_idx_x_;
    int y = cell_height_off + cell_height * start_idx_y_;
    DrawStart(&painter, x, y, cell_width, cell_height);
  }
  if (end_selected_) {
    int x = cell_width_off + cell_width * end_idx_x_;
    int y = cell_height_off + cell_height * end_idx_y_;
    DrawEnd(&painter, x, y, cell_width, cell_height);
  }

  painter.setPen(kColorWall_);
  for (size_t i = 0; i < maze_height_; ++i) {
    int current_y = cell_height_off + cell_height * i;
    DrawVerticalWall(&painter, cell_width_off, current_y, cell_height);
  }

  for (size_t i = 0; i < maze_width_; ++i) {
    int current_x = cell_width_off + cell_width * i;
    DrawHorisontalWall(&painter, current_x, cell_height_off, cell_width);
  }

  for (mtlc::Matrix<bool>::size_type i = 0; i < vertical_wall_.GetRows(); ++i) {
    for (mtlc::Matrix<bool>::size_type j = 0; j < vertical_wall_.GetCols();
         ++j) {
      if (vertical_wall_(i, j)) {
        int current_x = cell_width_off + cell_width * j + cell_width;
        int current_y = cell_height_off + cell_height * i;
        DrawVerticalWall(&painter, current_x, current_y, cell_height);
      }
    }
  }

  for (mtlc::Matrix<bool>::size_type i = 0; i < horisontal_wall_.GetRows();
       ++i) {
    for (mtlc::Matrix<bool>::size_type j = 0; j < horisontal_wall_.GetCols();
         ++j) {
      if (horisontal_wall_(i, j)) {
        int current_x = cell_width_off + cell_width * j;
        int current_y = cell_height_off + cell_height * i + cell_height;
        DrawHorisontalWall(&painter, current_x, current_y, cell_width);
      }
    }
  }

  if (need_solution_) {
    QPen pen(kColorWay_);
    pen.setWidth(2);
    painter.setPen(pen);
    for (size_t i = 0; i < solution_.size() - 1; i += 1) {
      int cur_x = cell_width_off + cell_width * solution_[i].x + cell_width / 2;
      int cur_y =
          cell_height_off + cell_height * solution_[i].y + cell_height / 2;
      int next_x =
          cell_width_off + cell_width * solution_[i + 1].x + cell_width / 2;
      int next_y =
          cell_height_off + cell_height * solution_[i + 1].y + cell_height / 2;
      painter.drawLine(cur_x, cur_y, next_x, next_y);
    }
  }
}

void WidgetMaze::DrawStart(QPainter *painter, int x, int y, int w, int h) {
  painter->fillRect(x, y, w, h, QColor(255, 0, 0));
}

void WidgetMaze::DrawEnd(QPainter *painter, int x, int y, int w, int h) {
  painter->fillRect(x, y, w, h, QColor(0, 255, 0));
}

void WidgetMaze::DrawVerticalWall(QPainter *painter, int x, int y, int size) {
  int start_x = x - kWidthWall_ / 2;
  for (int i = 0; i < kWidthWall_; ++i) {
    painter->drawLine(start_x + i, y, start_x + i, y + size);
  }
}

void WidgetMaze::DrawHorisontalWall(QPainter *painter, int x, int y, int size) {
  int start_y = y - kWidthWall_ / 2;
  for (int i = 0; i < kWidthWall_; ++i) {
    painter->drawLine(x, start_y + i, x + size, start_y + i);
  }
}

void WidgetMaze::mousePressEvent(QMouseEvent *event) {
  event->accept();

  int cell_x = (event->pos().x() / (width() / maze_width_));
  int cell_y = (event->pos().y() / (height() / maze_height_));
  if (cell_x < 0 || cell_x >= static_cast<int>(maze_width_)) return;
  if (cell_y < 0 || cell_y >= static_cast<int>(maze_height_)) return;

  if (event->button() == Qt::LeftButton) {
    emit SignalStartSelected(cell_x, cell_y);

  } else if (event->button() == Qt::RightButton) {
    emit SignalEndSelected(cell_x, cell_y);
  }
}

void WidgetMaze::SetMazeWidth(size_t maze_width) { maze_width_ = maze_width; }

void WidgetMaze::SetMazeHeight(size_t maze_height) {
  maze_height_ = maze_height;
}

void WidgetMaze::SetVerticalWall(mtlc::Matrix<bool> vertical_wall) {
  vertical_wall_ = vertical_wall;
}

void WidgetMaze::SetHorisontalWall(mtlc::Matrix<bool> horisontal_wall) {
  horisontal_wall_ = horisontal_wall;
}

void WidgetMaze::SetNeedSolution(bool need_solution) {
  need_solution_ = need_solution;
}

void WidgetMaze::SetSolution(std::vector<Point> solution) {
  solution_ = solution;
}

void WidgetMaze::SetStartSelected(bool start_selected) {
  start_selected_ = start_selected;
}

void WidgetMaze::SetEndSelected(bool end_selected) {
  end_selected_ = end_selected;
}

void WidgetMaze::SetStartIdx(size_t start_idx_x, size_t start_idx_y) {
  start_idx_x_ = start_idx_x;
  start_idx_y_ = start_idx_y;
}

void WidgetMaze::SetEndIdx(size_t end_idx_x, size_t end_idx_y) {
  end_idx_x_ = end_idx_x;
  end_idx_y_ = end_idx_y;
}

const QColor WidgetMaze::kColorCell_ = QColor(255, 255, 255);
const QColor WidgetMaze::kColorWall_ = QColor(0, 0, 0);
const QColor WidgetMaze::kColorWay_ = QColor(156, 72, 240);

const int WidgetMaze::kWidthWall_ = 2;

}  // namespace mc
