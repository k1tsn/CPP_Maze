#ifndef MAZE_VIEW_MAINWINDOW_H_
#define MAZE_VIEW_MAINWINDOW_H_

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QWidget>
#include <string>
#include <vector>

#include "controller/controller.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace mc {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller* controller, QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  // ----------------------------------------------------------------------- //
  //                               Maze slots                                //
  // ----------------------------------------------------------------------- //

  void SlotMazeImportFromFile();
  void SlotMazeExportToFile();
  void SlotMazeGenIdeal();
  void SlotMazeSolve();

  void SlotMazeStartSelected(size_t start_idx_x, size_t start_idx_y);
  void SlotMazeEndSelected(size_t end_idx_x, size_t end_idx_y);

  void SlotMazeLineStartXChanged();
  void SlotMazeLineStartYChanged();
  void SlotMazeLineEndXChanged();
  void SlotMazeLineEndYChanged();

  // ----------------------------------------------------------------------- //
  //                               Cave slots                                //
  // ----------------------------------------------------------------------- //

  void SlotCaveImportFromFile();
  void SlotCaveExportToFile();
  void SlotCaveCreateRandom();
  void SlotCaveNextIteration();
  void SlotCaveAutoIteration();
  void SlotCaveIterTimeout();

 private:
  // ----------------------------------------------------------------------- //
  //                                 Maze                                    //
  // ----------------------------------------------------------------------- //

  void MazeSetInfo(const QString& msg);
  void MazeCleanInfo();
  void MazeUpdate();
  void MazeCleanSol();

  // ----------------------------------------------------------------------- //
  //                                 Cave                                    //
  // ----------------------------------------------------------------------- //

  void CaveLockControll();
  void CaveUnlockControll();

  void CaveSetInfo(const QString& msg);
  void CaveCleanInfo();
  void CaveUpdate();

  // ----------------------------------------------------------------------- //
  //                                 Setup                                   //
  // ----------------------------------------------------------------------- //

  void Connects();

  static const QString kStrErrorUndefinedError;
  static const QString kStrErrorFileDontCreate;
  static const QString kStrErrorFileDontOpen;
  static const QString kStrErrorInvalidFile;
  static const QString kStrErrorNoMazeToExport;
  static const QString kStrErrorNoCaveToExport;
  static const QString kStrErrorInvMazeSize;
  static const QString kStrErrorInvStartPoint;
  static const QString kStrErrorInvEndPoint;
  static const QString kStrErrorNoSolution;
  static const QString kStrErrorStartEndInSamePosition;
  static const QString kStrErrorInvChance;
  static const QString kStrErrorInvLimits;
  static const QString kStrErrorInvPeriod;
  static const QString kStrErrorInvSize;
  static const QString kStrErrorInvData;

  static const QString kStrSaveFileText;

  ::Ui::MainWindow* ui_;
  Controller* controller_;

  QTimer cave_iter_timer_;
  int cave_iter_timer_interval_;
  bool auto_iteration_active_;

  bool need_solution_;
  std::vector<Controller::Point> solution_;
};

}  // namespace mc

#endif  // MAZE_VIEW_MAINWINDOW_H_
