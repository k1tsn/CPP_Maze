// qt view

#include "qt_view.h"

#include <QApplication>

#include "controller/controller.h"
#include "mainwindow.h"
#include "view/view.h"

namespace mc {

QTView::QTView(int& argc, char** argv, Controller* controller) {
  a_ = new QApplication(argc, argv);
  w_ = new MainWindow(controller);
}

QTView::~QTView() {
  delete w_;
  delete a_;
}

int QTView::Exec() {
  w_->show();
  return a_->exec();
}

}  // namespace mc
