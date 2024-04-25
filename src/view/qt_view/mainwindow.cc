#include "mainwindow.h"

#include <QFileDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QWidget>
#include <string>

#include "controller/controller.h"
#include "ui_mainwindow.h"
#include "widget_cave.h"
#include "widget_maze.h"

namespace mc {

MainWindow::MainWindow(Controller* controller, QWidget* parent)
    : QMainWindow(parent), ui_(new ::Ui::MainWindow), controller_(controller) {
  ui_->setupUi(this);
  Connects();

  auto_iteration_active_ = false;
  need_solution_ = false;

  CaveUpdate();
  MazeUpdate();
}

MainWindow::~MainWindow() { delete ui_; }

// ------------------------------------------------------------------------- //
//                                Maze slots                                 //
// ------------------------------------------------------------------------- //

void MainWindow::SlotMazeImportFromFile() {
  need_solution_ = false;
  MazeCleanInfo();

  QString qfilename = QFileDialog::getOpenFileName(this, tr("Выбрать файл"),
                                                   "~", tr("*.txt (*.txt)"));
  std::string filename = qfilename.toStdString();
  Controller::ReturnCode code = controller_->MazeImport(filename);
  switch (code) {
    case Controller::ReturnCode::kCodeOk:
      MazeUpdate();
      break;

    case Controller::ReturnCode::kCodeFileDontOpen:
      MazeSetInfo(kStrErrorFileDontOpen);
      break;

    case Controller::ReturnCode::kCodeInvalidFile:
      MazeSetInfo(kStrErrorInvalidFile);
      break;

    default:
      MazeSetInfo(kStrErrorUndefinedError);
      break;
  }
}

void MainWindow::SlotMazeExportToFile() {
  MazeCleanInfo();

  QString qfilename = QFileDialog::getSaveFileName(this, tr("Выбрать файл"),
                                                   "~", tr("*.txt (*.txt)"));
  QString msg = kStrSaveFileText;
  msg += qfilename;
  std::string filename = qfilename.toStdString();
  Controller::ReturnCode code = controller_->MazeExport(filename);
  switch (code) {
    case Controller::ReturnCode::kCodeOk:
      MazeSetInfo(msg);
      break;

    case Controller::ReturnCode::kCodeFileDontCreate:
      MazeSetInfo(kStrErrorFileDontCreate);
      break;

    default:
      MazeSetInfo(kStrErrorUndefinedError);
      break;
  }
}

void MainWindow::SlotMazeGenIdeal() {
  need_solution_ = false;
  MazeCleanInfo();

  bool width_ok, height_ok;
  qulonglong width =
      ui_->lineEdit_maze_gen_ideal_width->text().toULongLong(&width_ok);
  qulonglong height =
      ui_->lineEdit_maze_gen_ideal_height->text().toULongLong(&height_ok);

  if (!width_ok || !height_ok) {
    MazeSetInfo(kStrErrorInvMazeSize);
    return;
  }

  Controller::size_type w = static_cast<Controller::size_type>(width);
  Controller::size_type h = static_cast<Controller::size_type>(height);
  Controller::ReturnCode code = controller_->GenIdealMaze(w, h);
  switch (code) {
    case Controller::ReturnCode::kCodeOk:
      MazeUpdate();
      break;

    case Controller::ReturnCode::kCodeInvalidSizeGiven:
      MazeSetInfo(kStrErrorInvMazeSize);
      break;

    default:
      MazeSetInfo(kStrErrorUndefinedError);
      break;
  }
}

void MainWindow::SlotMazeSolve() {
  need_solution_ = false;
  MazeCleanInfo();

  bool start_x_ok, start_y_ok, end_x_ok, end_y_ok;
  qulonglong start_x =
      ui_->lineEdit_maze_solve_range_start_x->text().toULongLong(&start_x_ok);
  qulonglong start_y =
      ui_->lineEdit_maze_solve_range_start_y->text().toULongLong(&start_y_ok);
  qulonglong end_x =
      ui_->lineEdit_maze_solve_range_end_x->text().toULongLong(&end_x_ok);
  qulonglong end_y =
      ui_->lineEdit_maze_solve_range_end_y->text().toULongLong(&end_y_ok);

  if (!start_x_ok || !start_y_ok) {
    MazeSetInfo(kStrErrorInvStartPoint);
    return;

  } else if (!end_x_ok || !end_y_ok) {
    MazeSetInfo(kStrErrorInvEndPoint);
    return;
  }

  Controller::Point start{static_cast<int>(start_x), static_cast<int>(start_y)};
  Controller::Point end{static_cast<int>(end_x), static_cast<int>(end_y)};
  Controller::ReturnCode code =
      controller_->GetSolutionMaze(start, end, solution_);
  switch (code) {
    case Controller::ReturnCode::kCodeOk:
      need_solution_ = true;
      MazeUpdate();
      break;

    case Controller::ReturnCode::kCodeMazeNoSolution:
      MazeSetInfo(kStrErrorNoSolution);
      break;

    case Controller::ReturnCode::kCodeStartEndInSamePosition:
      MazeSetInfo(kStrErrorStartEndInSamePosition);
      break;

    default:
      MazeSetInfo(kStrErrorUndefinedError);
      break;
  }
}

void MainWindow::SlotMazeStartSelected(size_t start_idx_x, size_t start_idx_y) {
  need_solution_ = false;
  ui_->lineEdit_maze_solve_range_start_x->setText(QString::number(start_idx_x));
  ui_->lineEdit_maze_solve_range_start_y->setText(QString::number(start_idx_y));
}

void MainWindow::SlotMazeEndSelected(size_t end_idx_x, size_t end_idx_y) {
  need_solution_ = false;
  ui_->lineEdit_maze_solve_range_end_x->setText(QString::number(end_idx_x));
  ui_->lineEdit_maze_solve_range_end_y->setText(QString::number(end_idx_y));
}

void MainWindow::SlotMazeLineStartXChanged() {
  need_solution_ = false;
  MazeCleanInfo();
  MazeUpdate();
}

void MainWindow::SlotMazeLineStartYChanged() {
  need_solution_ = false;
  MazeCleanInfo();
  MazeUpdate();
}

void MainWindow::SlotMazeLineEndXChanged() {
  need_solution_ = false;
  MazeCleanInfo();
  MazeUpdate();
}

void MainWindow::SlotMazeLineEndYChanged() {
  need_solution_ = false;
  MazeCleanInfo();
  MazeUpdate();
}

// ------------------------------------------------------------------------- //
//                                Cave slots                                 //
// ------------------------------------------------------------------------- //

void MainWindow::SlotCaveImportFromFile() {
  CaveCleanInfo();

  QString qfilename = QFileDialog::getOpenFileName(this, tr("Выбрать файл"),
                                                   "~", tr("*.txt (*.txt)"));
  std::string filename = qfilename.toStdString();
  Controller::ReturnCode code = controller_->CaveImport(filename);
  switch (code) {
    case Controller::ReturnCode::kCodeOk:
      CaveUpdate();
      break;

    case Controller::ReturnCode::kCodeFileDontOpen:
      CaveSetInfo(kStrErrorFileDontOpen);
      break;

    case Controller::ReturnCode::kCodeInvalidFile:
      CaveSetInfo(kStrErrorInvalidFile);
      break;

    default:
      CaveSetInfo(kStrErrorUndefinedError);
      break;
  }
}

void MainWindow::SlotCaveExportToFile() {
  CaveCleanInfo();

  QString qfilename = QFileDialog::getSaveFileName(this, tr("Выбрать файл"),
                                                   "~", tr("*.txt (*.txt)"));
  QString msg = kStrSaveFileText;
  msg += qfilename;
  std::string filename = qfilename.toStdString();
  Controller::ReturnCode code = controller_->CaveExport(filename);
  switch (code) {
    case Controller::ReturnCode::kCodeOk:
      CaveSetInfo(msg);
      break;

    case Controller::ReturnCode::kCodeFileDontCreate:
      CaveSetInfo(kStrErrorFileDontCreate);
      break;

    default:
      CaveSetInfo(kStrErrorUndefinedError);
      break;
  }
}

void MainWindow::SlotCaveCreateRandom() {
  CaveCleanInfo();

  bool chance_ok, w_ok, h_ok;
  qulonglong chance =
      ui_->lineEdit_cave_settings_chance->text().toULongLong(&chance_ok);
  if (!chance_ok) {
    CaveSetInfo(kStrErrorInvChance);
    return;
  }
  qulonglong w = ui_->lineEdit_cave_settings_width->text().toULongLong(&w_ok);
  qulonglong h = ui_->lineEdit_cave_settings_height->text().toULongLong(&h_ok);
  if (!w_ok || !h_ok) {
    CaveSetInfo(kStrErrorInvSize);
    return;
  }

  Controller::ReturnCode code = controller_->CaveSetRandom(
      static_cast<int>(chance), static_cast<int>(w), static_cast<int>(h));
  switch (code) {
    case Controller::ReturnCode::kCodeOk:
      CaveUpdate();
      break;

    case Controller::ReturnCode::kCodeInvalidData:
      CaveSetInfo(kStrErrorInvData);
      break;

    default:
      CaveSetInfo(kStrErrorUndefinedError);
      break;
  }
}

void MainWindow::SlotCaveNextIteration() {
  CaveCleanInfo();

  bool birth_limit_ok, death_limit_ok;
  qulonglong birth =
      ui_->lineEdit_cave_settings_birdth->text().toULongLong(&birth_limit_ok);
  qulonglong death =
      ui_->lineEdit_cave_settings_death->text().toULongLong(&death_limit_ok);

  if (!birth_limit_ok || !death_limit_ok) {
    CaveSetInfo(kStrErrorInvLimits);
    return;
  }

  Controller::ReturnCode code = controller_->CaveNextIteration(
      static_cast<int>(birth), static_cast<int>(death));
  switch (code) {
    case Controller::ReturnCode::kCodeOk:
      CaveUpdate();
      break;

    case Controller::ReturnCode::kCodeCaveNextGenNotChange:
      break;

    default:
      CaveSetInfo(kStrErrorUndefinedError);
      break;
  }
}

void MainWindow::SlotCaveAutoIteration() {
  if (auto_iteration_active_) {
    cave_iter_timer_.stop();
    CaveUnlockControll();
    auto_iteration_active_ = false;
    return;
  }

  CaveCleanInfo();

  bool birth_limit_ok, death_limit_ok;
  ui_->lineEdit_cave_settings_birdth->text().toULongLong(&birth_limit_ok);
  ui_->lineEdit_cave_settings_death->text().toULongLong(&death_limit_ok);

  if (!birth_limit_ok || !death_limit_ok) {
    CaveSetInfo(kStrErrorInvLimits);
    return;
  }

  bool interval;
  qulonglong value = ui_->lineEdit_cave_interval->text().toULongLong(&interval);
  if (!interval) {
    CaveSetInfo(kStrErrorInvPeriod);
    return;
  }

  cave_iter_timer_interval_ = value;
  cave_iter_timer_.start(cave_iter_timer_interval_);
  CaveLockControll();
  auto_iteration_active_ = true;
}

void MainWindow::SlotCaveIterTimeout() {
  bool birth_limit_ok, death_limit_ok;
  qulonglong birth =
      ui_->lineEdit_cave_settings_birdth->text().toULongLong(&birth_limit_ok);
  qulonglong death =
      ui_->lineEdit_cave_settings_death->text().toULongLong(&death_limit_ok);

  Controller::ReturnCode code = controller_->CaveNextIteration(
      static_cast<int>(birth), static_cast<int>(death));
  switch (code) {
    case Controller::ReturnCode::kCodeOk:
      CaveUpdate();
      cave_iter_timer_.start(cave_iter_timer_interval_);
      break;

    case Controller::ReturnCode::kCodeCaveNextGenNotChange:
      CaveUnlockControll();
      cave_iter_timer_.stop();
      auto_iteration_active_ = false;
      break;

    default:
      CaveSetInfo(kStrErrorUndefinedError);
      CaveUnlockControll();
      cave_iter_timer_.stop();
      auto_iteration_active_ = false;
      break;
  }
}

// ------------------------------------------------------------------------- //
//                                  Maze                                     //
// ------------------------------------------------------------------------- //

void MainWindow::MazeSetInfo(const QString& msg) {
  ui_->label_maze_info_line->setText(msg);
}

void MainWindow::MazeCleanInfo() { ui_->label_maze_info_line->clear(); }

void MainWindow::MazeUpdate() {
  Controller::size_type w = controller_->GetWidthMaze();
  Controller::size_type h = controller_->GetHeightMaze();

  ui_->widget_maze->SetMazeWidth(static_cast<size_t>(w));
  ui_->widget_maze->SetMazeHeight(static_cast<size_t>(h));
  ui_->widget_maze->SetHorisontalWall(controller_->GetHorisontalWallsMaze());
  ui_->widget_maze->SetVerticalWall(controller_->GetVerticalWallsMaze());

  std::vector<WidgetMaze::Point> maze_solution(solution_.size());
  for (size_t i = 0; i < solution_.size(); ++i) {
    WidgetMaze::Point point = {solution_[i].x, solution_[i].y};
    maze_solution[i] = point;
  }
  ui_->widget_maze->SetSolution(maze_solution);

  ui_->widget_maze->SetNeedSolution(need_solution_);

  bool start_x_ok, start_y_ok, end_x_ok, end_y_ok;
  qulonglong start_x =
      ui_->lineEdit_maze_solve_range_start_x->text().toULongLong(&start_x_ok);
  qulonglong start_y =
      ui_->lineEdit_maze_solve_range_start_y->text().toULongLong(&start_y_ok);
  qulonglong end_x =
      ui_->lineEdit_maze_solve_range_end_x->text().toULongLong(&end_x_ok);
  qulonglong end_y =
      ui_->lineEdit_maze_solve_range_end_y->text().toULongLong(&end_y_ok);

  ui_->widget_maze->SetStartSelected((start_x_ok && start_y_ok));
  ui_->widget_maze->SetEndSelected((end_x_ok && end_y_ok));

  ui_->widget_maze->SetStartIdx(start_x, start_y);
  ui_->widget_maze->SetEndIdx(end_x, end_y);

  ui_->widget_maze->update();
}

void MainWindow::MazeCleanSol() { ui_->widget_maze->SetNeedSolution(false); }

// ------------------------------------------------------------------------- //
//                                  Cave                                     //
// ------------------------------------------------------------------------- //

void MainWindow::CaveLockControll() {
  ui_->pushButton_cave_create_random->setEnabled(false);
  ui_->pushButton_cave_export->setEnabled(false);
  ui_->pushButton_cave_import->setEnabled(false);
  ui_->pushButton_cave_next_iteration->setEnabled(false);

  ui_->lineEdit_cave_interval->setEnabled(false);
  ui_->lineEdit_cave_settings_birdth->setEnabled(false);
  ui_->lineEdit_cave_settings_chance->setEnabled(false);
  ui_->lineEdit_cave_settings_death->setEnabled(false);
  ui_->lineEdit_cave_settings_height->setEnabled(false);
  ui_->lineEdit_cave_settings_width->setEnabled(false);
}

void MainWindow::CaveUnlockControll() {
  ui_->pushButton_cave_create_random->setEnabled(true);
  ui_->pushButton_cave_export->setEnabled(true);
  ui_->pushButton_cave_import->setEnabled(true);
  ui_->pushButton_cave_next_iteration->setEnabled(true);

  ui_->lineEdit_cave_interval->setEnabled(true);
  ui_->lineEdit_cave_settings_birdth->setEnabled(true);
  ui_->lineEdit_cave_settings_chance->setEnabled(true);
  ui_->lineEdit_cave_settings_death->setEnabled(true);
  ui_->lineEdit_cave_settings_height->setEnabled(true);
  ui_->lineEdit_cave_settings_width->setEnabled(true);
}

void MainWindow::CaveSetInfo(const QString& msg) {
  ui_->label_cave_info_line->setText(msg);
}

void MainWindow::CaveCleanInfo() { ui_->label_cave_info_line->clear(); }

void MainWindow::CaveUpdate() {
  Controller::size_type w = controller_->GetWidthCave();
  Controller::size_type h = controller_->GetHeightCave();

  ui_->widget_cave->SetCaveWidth(static_cast<size_t>(w));
  ui_->widget_cave->SetCaveHeight(static_cast<size_t>(h));
  ui_->widget_cave->SetCaveMatrix(controller_->GetCaveMatrix());

  ui_->widget_cave->update();
}

// ------------------------------------------------------------------------- //
//                                  Setup                                    //
// ------------------------------------------------------------------------- //

void MainWindow::Connects() {
  connect(ui_->pushButton_maze_import, &QPushButton::pressed, this,
          &MainWindow::SlotMazeImportFromFile);
  connect(ui_->pushButton_maze_export, &QPushButton::pressed, this,
          &MainWindow::SlotMazeExportToFile);
  connect(ui_->pushButton_maze_gen_ideal, &QPushButton::pressed, this,
          &MainWindow::SlotMazeGenIdeal);
  connect(ui_->pushButton_maze_solve, &QPushButton::pressed, this,
          &MainWindow::SlotMazeSolve);

  connect(ui_->pushButton_cave_import, &QPushButton::pressed, this,
          &MainWindow::SlotCaveImportFromFile);
  connect(ui_->pushButton_cave_export, &QPushButton::pressed, this,
          &MainWindow::SlotCaveExportToFile);
  connect(ui_->pushButton_cave_create_random, &QPushButton::pressed, this,
          &MainWindow::SlotCaveCreateRandom);
  connect(ui_->pushButton_cave_next_iteration, &QPushButton::pressed, this,
          &MainWindow::SlotCaveNextIteration);
  connect(ui_->pushButton_cave_auto_iteration, &QPushButton::pressed, this,
          &MainWindow::SlotCaveAutoIteration);

  connect(ui_->widget_maze, &WidgetMaze::SignalStartSelected, this,
          &MainWindow::SlotMazeStartSelected);
  connect(ui_->widget_maze, &WidgetMaze::SignalEndSelected, this,
          &MainWindow::SlotMazeEndSelected);

  connect(ui_->lineEdit_maze_solve_range_end_x, &QLineEdit::textChanged, this,
          &MainWindow::SlotMazeLineEndXChanged);
  connect(ui_->lineEdit_maze_solve_range_end_y, &QLineEdit::textChanged, this,
          &MainWindow::SlotMazeLineEndYChanged);
  connect(ui_->lineEdit_maze_solve_range_start_x, &QLineEdit::textChanged, this,
          &MainWindow::SlotMazeLineStartXChanged);
  connect(ui_->lineEdit_maze_solve_range_start_y, &QLineEdit::textChanged, this,
          &MainWindow::SlotMazeLineStartYChanged);

  connect(&cave_iter_timer_, &QTimer::timeout, this,
          &MainWindow::SlotCaveIterTimeout);
}

const QString MainWindow::kStrErrorUndefinedError = "Произошла ошибка";
const QString MainWindow::kStrErrorFileDontCreate = "Файл не сохранен";
const QString MainWindow::kStrErrorFileDontOpen = "Файл не открыт";
const QString MainWindow::kStrErrorInvalidFile = "Неккоректный файл";
const QString MainWindow::kStrErrorNoMazeToExport =
    "Нет лабиринта для сохранения";
const QString MainWindow::kStrErrorNoCaveToExport = "Нет пещеры для сохранения";
const QString MainWindow::kStrErrorInvMazeSize =
    "Неккоректные размеры лабиринта";
const QString MainWindow::kStrErrorInvStartPoint =
    "Неккоректная точка начала лабиринта";
const QString MainWindow::kStrErrorInvEndPoint =
    "Некорректная точка конца лабириринта";
const QString MainWindow::kStrErrorNoSolution = "Нет решения";
const QString MainWindow::kStrErrorStartEndInSamePosition =
    "Начало и конец в одной точке";
const QString MainWindow::kStrErrorInvChance = "Неккоректный шанс";
const QString MainWindow::kStrErrorInvLimits = "Неккоректные лимиты";
const QString MainWindow::kStrErrorInvPeriod = "Неккоректный интервал";
const QString MainWindow::kStrErrorInvSize = "Неккоректные размеры";
const QString MainWindow::kStrErrorInvData = "Неккоректные данные";

const QString MainWindow::kStrSaveFileText = "Файл сохранен: ";

}  // namespace mc
