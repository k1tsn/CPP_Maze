// qt view

#include <QApplication>

#include "controller/controller.h"
#include "mainwindow.h"
#include "view/view.h"

namespace mc {

class QTView : public View {
 public:
  QTView(int& argc, char** argv, Controller* controller);
  QTView(const QTView& other) = delete;
  QTView(QTView&& other) noexcept = delete;
  QTView& operator=(const QTView& other) = delete;
  QTView& operator=(QTView&& other) noexcept = delete;
  virtual ~QTView();

  int Exec() override;

 private:
  QApplication* a_;
  MainWindow* w_;
};

}  // namespace mc
