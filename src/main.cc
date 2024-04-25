#include <QApplication>

#include "controller/controller.h"
#include "controller/controller_default.h"
#include "model/model.h"
#include "view/qt_view/qt_view.h"
#include "view/view.h"

int main(int argc, char** argv) {
  mc::Model* model = new mc::Model();
  mc::Controller* controller = new mc::ControllerDefault(model);
  mc::View* view = new mc::QTView(argc, argv, controller);

  int code = view->Exec();

  delete view;
  delete controller;
  delete model;

  return code;
}
