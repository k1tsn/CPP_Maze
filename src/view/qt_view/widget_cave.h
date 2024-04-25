// widget maze

#ifndef MAZE_VIEW_WIDGET_CAVE_H_
#define MAZE_VIEW_WIDGET_CAVE_H_

#include <QColor>
#include <QPaintEvent>
#include <QWidget>
#include <cstddef>

#include "matrix.h"

namespace mc {

class WidgetCave : public QWidget {
  Q_OBJECT

 public:
  WidgetCave(QWidget *parent = nullptr);
  virtual ~WidgetCave();

  void SetCaveWidth(size_t cave_width);
  void SetCaveHeight(size_t cave_height);
  void SetCaveMatrix(const mtlc::Matrix<bool> &cave_matrix);

 private:
  void paintEvent(QPaintEvent *event) override;

  static const QColor kColorLive;
  static const QColor kColorDeath;

  size_t cave_width_;
  size_t cave_height_;
  mtlc::Matrix<bool> cave_matrix_;
};

}  // namespace mc

#endif  // MAZE_VIEW_WIDGET_CAVE_H_
