// controller default

#ifndef MAZE_CONTROLLER_CONTROLLER_DEFAULT_H_
#define MAZE_CONTROLLER_CONTROLLER_DEFAULT_H_

#include <string>

#include "controller.h"
#include "model/model.h"

namespace mc {

class ControllerDefault : public Controller {
 public:
  using ReturnCode = Controller::ReturnCode;
  using size_type = Controller::size_type;
  using Point = Controller::Point;
  using MazeWallMatrix = Controller::MazeWallMatrix;
  using CaveMatrix = Controller::CaveMatrix;

  ControllerDefault(Model* model);
  virtual ~ControllerDefault();

  // ----------------------------------------------------------------------- //
  //                                 Maze                                    //
  // ----------------------------------------------------------------------- //

  ReturnCode MazeImport(const std::string& filename) override;
  ReturnCode MazeExport(const std::string& filename) override;
  ReturnCode GenIdealMaze(size_type width, size_type height) override;

  ReturnCode GetSolutionMaze(Point start, Point end,
                             std::vector<Point>& points) override;

  size_type GetWidthMaze() override;
  size_type GetHeightMaze() override;
  MazeWallMatrix GetVerticalWallsMaze() override;
  MazeWallMatrix GetHorisontalWallsMaze() override;

  // ----------------------------------------------------------------------- //
  //                                 Cave                                    //
  // ----------------------------------------------------------------------- //

  /// @brief Import cave from file
  /// @return kCodeOk if ok
  /// @return kCodeFileDontOpen if file dont open
  /// @return kCodeInvalidfile if file invalid
  ReturnCode CaveImport(const std::string& filename) override;

  /// @brief Export cave to file
  /// @return kCodeOk if ok
  /// @return kCodeFileDontCreate if file dont save
  ReturnCode CaveExport(const std::string& filename) const override;

  /// @brief Set random values cave
  /// @param chance chance to cell will live
  /// @param w cave width
  /// @param h cave height
  /// @return kCodeOk if ok.
  /// @return kCodeInvData if chance not in [0, 100] or w not in [1, 50] or h
  /// not in [1, 50].
  ReturnCode CaveSetRandom(int chance, int w, int h) override;

  /// @brief Next iteration cell automat
  /// @param birth_limit
  /// @param death_limit
  /// @return kCodeOk if ok.
  /// @return kCodeInvData if limits not in range [0, 7].
  /// @return kCodeCaveNextGenNotChange if cave dont change
  ReturnCode CaveNextIteration(int birth_limit, int death_limit) override;

  size_type GetWidthCave() const override;
  size_type GetHeightCave() const override;
  CaveMatrix GetCaveMatrix() const override;

 private:
  Model* model_;
};

}  // namespace mc

#endif  // MAZE_CONTROLLER_CONTROLLER_DEFAULT_H_
