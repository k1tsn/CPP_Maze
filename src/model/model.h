// fasade model

#ifndef MAZE_MODEL_MODEL_H_
#define MAZE_MODEL_MODEL_H_

#include <cstddef>
#include <string>

#include "cave/cave.h"
#include "matrix.h"
#include "maze/maze.h"

namespace mc {

class Model {
 public:
  using size_type = size_t;
  using Point = Maze::Point;
  using MazeWallMatrix = Maze::MazeWallMatrix;
  using CaveMatrix = Cave::CaveMatrix;

  enum ReturnCode {
    kCodeOk,
    kCodeFileDontCreate,
    kCodeFileDontOpen,
    kCodeInvalidFile,
    kCodeNoMazeToExport,
    kCodeNoCaveToExport,
    kCodeInvalidSizeGiven,
    kCodeInvalidData,
    kCodeCaveNextGenNotChange,
    kCodeMazeNoSolution,
    kCodeUnderfinedFileType,
    kCodeStartEndInSamePosition,
  };

  Model();
  virtual ~Model();

  // ----------------------------------------------------------------------- //
  //                                 Maze                                    //
  // ----------------------------------------------------------------------- //

  /// @brief Import maze from file
  /// @return Return error code
  ReturnCode MazeImport(const std::string& filename);

  /// @brief Exprot maze from file
  /// @return Return error code
  ReturnCode MazeExport(const std::string& filename);

  /// @brief Creates a perfect maze using the Eller algorithm
  /// @param rows Hight
  /// @param columns Weight
  /// @param rand A non-zero value disables the randomizer, each time the same
  /// algorithm will be generated for a certain number
  /// @return Return error code
  ReturnCode CreatePerfectMaze(size_type rows, size_type columns, int rand = 0);

  /// @brief Solves pathfinding with a wave algorithm
  /// @param points Path coordinates
  /// @return Return error code
  ReturnCode GetSolutionMaze(Point start, Point end,
                             std::vector<Point>& points);

  size_type GetWidthMaze();
  size_type GetHeightMaze();

  MazeWallMatrix GetVerticalWallsMaze();
  MazeWallMatrix GetHorisontalWallsMaze();

  // ----------------------------------------------------------------------- //
  //                                 Cave                                    //
  // ----------------------------------------------------------------------- //

  /// @brief Import cave from file
  /// @return kCodeOk if ok
  /// @return kCodeFileDontOpen if file dont open
  /// @return kCodeInvalidfile if file invalid
  ReturnCode CaveImport(const std::string& filename);

  /// @brief Export cave to file
  /// @return kCodeOk if ok
  /// @return kCodeFileDontCreate if file dont save
  ReturnCode CaveExport(const std::string& filename) const;

  /// @brief Set random values cave
  /// @param chance chance to cell will live
  /// @param w cave width
  /// @param h cave height
  /// @return kCodeOk if ok.
  /// @return kCodeInvData if chance not in [0, 100] or w not in [1, 50] or h
  /// not in [1, 50].
  ReturnCode CaveSetRandom(int chance, int w, int h);

  /// @brief Next iteration cell automat
  /// @param birth_limit
  /// @param death_limit
  /// @return kCodeOk if ok.
  /// @return kCodeInvData if limits not in range [0, 7].
  /// @return kCodeCaveNextGenNotChange if cave dont change
  ReturnCode CaveNextIteration(int birth_limit, int death_limit);

  size_type GetWidthCave() const;
  size_type GetHeightCave() const;
  CaveMatrix GetCaveMatrix() const;

 private:
  static ReturnCode MazeCodeConvert(Maze::ReturnCode code);
  static ReturnCode CaveCodeConvert(Cave::ReturnCode code);

  Maze maze_;
  Cave cave_;
};

}  // namespace mc

#endif  // MAZE_MODEL_MODEL_H_
