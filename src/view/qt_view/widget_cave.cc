// widget maze

#include "widget_cave.h"

#include <QColor>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <cstddef>

#include "matrix.h"

namespace mc {

WidgetCave::WidgetCave(QWidget *parent) : QWidget(parent) {
  cave_width_ = 1;
  cave_height_ = 1;
  cave_matrix_ = mtlc::Matrix<bool>(1, 1);
  cave_matrix_(0, 0) = true;
}

WidgetCave::~WidgetCave() {}

void WidgetCave::SetCaveWidth(size_t cave_width) { cave_width_ = cave_width; }

void WidgetCave::SetCaveHeight(size_t cave_height) {
  cave_height_ = cave_height;
}

void WidgetCave::SetCaveMatrix(const mtlc::Matrix<bool> &cave_matrix) {
  cave_matrix_ = cave_matrix;
}

void WidgetCave::paintEvent(QPaintEvent *event) {
  event->accept();

  QPainter painter(this);
  painter.fillRect(0, 0, width(), height(), kColorLive);

  int cell_width = width() / cave_width_;
  int cell_width_off = (width() - cell_width * cave_width_) / 2;
  int cell_height = height() / cave_height_;
  int cell_height_off = (height() - cell_height * cave_height_) / 2;

  for (mtlc::Matrix<bool>::size_type i = 0; i < cave_matrix_.GetRows(); ++i) {
    for (mtlc::Matrix<bool>::size_type j = 0; j < cave_matrix_.GetCols(); ++j) {
      if (!cave_matrix_(i, j)) continue;

      int current_x = cell_width_off + cell_width * j;
      int current_y = cell_height_off + cell_height * i;
      painter.fillRect(current_x, current_y, cell_width, cell_height,
                       kColorDeath);
    }
  }
}

const QColor WidgetCave::kColorLive = QColor(255, 255, 255);
const QColor WidgetCave::kColorDeath = QColor(0, 0, 0);

}  // namespace mc
