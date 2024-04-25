// interface controller

#ifndef MAZE_CONTROLLER_CONTROLLER_H_
#define MAZE_CONTROLLER_CONTROLLER_H_

#include <string>

#include "model/model.h"

namespace mc {

class Controller {
 public:
  using ReturnCode = Model::ReturnCode;
  using size_type = Model::size_type;
  using Point = Model::Point;
  using MazeWallMatrix = Model::MazeWallMatrix;
  using CaveMatrix = Model::CaveMatrix;

  Controller() {}
  virtual ~Controller() {}

  // ----------------------------------------------------------------------- //
  //                                 Maze                                    //
  // ----------------------------------------------------------------------- //

  virtual ReturnCode MazeImport(const std::string& filename) = 0;
  virtual ReturnCode MazeExport(const std::string& filename) = 0;
  virtual ReturnCode GenIdealMaze(size_type width, size_type height) = 0;

  virtual ReturnCode GetSolutionMaze(Point start, Point end,
                                     std::vector<Point>& points) = 0;

  virtual size_type GetWidthMaze() = 0;
  virtual size_type GetHeightMaze() = 0;
  virtual MazeWallMatrix GetVerticalWallsMaze() = 0;
  virtual MazeWallMatrix GetHorisontalWallsMaze() = 0;

  // ----------------------------------------------------------------------- //
  //                                 Cave                                    //
  // ----------------------------------------------------------------------- //

  /// @brief Import cave from file
  /// @return kCodeOk if ok
  /// @return kCodeFileDontOpen if file dont open
  /// @return kCodeInvalidfile if file invalid
  virtual ReturnCode CaveImport(const std::string& filename) = 0;

  /// @brief Export cave to file
  /// @return kCodeOk if ok
  /// @return kCodeFileDontCreate if file dont save
  virtual ReturnCode CaveExport(const std::string& filename) const = 0;

  /// @brief Set random values cave
  /// @param chance chance to cell will live
  /// @param w cave width
  /// @param h cave height
  /// @return kCodeOk if ok.
  /// @return kCodeInvData if chance not in [0, 100] or w not in [1, 50] or h
  /// not in [1, 50].
  virtual ReturnCode CaveSetRandom(int chance, int w, int h) = 0;

  /// @brief Next iteration cell automat
  /// @param birth_limit
  /// @param death_limit
  /// @return kCodeOk if ok.
  /// @return kCodeInvData if limits not in range [0, 7].
  /// @return kCodeCaveNextGenNotChange if cave dont change
  virtual ReturnCode CaveNextIteration(int birth_limit, int death_limit) = 0;

  virtual size_type GetWidthCave() const = 0;
  virtual size_type GetHeightCave() const = 0;
  virtual CaveMatrix GetCaveMatrix() const = 0;
};

}  // namespace mc

#endif  // MAZE_CONTROLLER_CONTROLLER_H_
