#include <QApplication>

#include "controller/controller.h"
#include "controller/controller_default.h"
#include "model/model.h"
#include "view/qt_view/qt_view.h"
#include "view/view.h"

int main(int argc, char** argv) {
  s21::Model* model = new s21::Model();
  s21::Controller* controller = new s21::ControllerDefault(model);
  s21::View* view = new s21::QTView(argc, argv, controller);

  int code = view->Exec();

  delete view;
  delete controller;
  delete model;

  return code;
}
