#ifndef MAZE_MODEL_MAZE_MAZE_H_
#define MAZE_MODEL_MAZE_MAZE_H_

#include <map>
#include <stack>
#include <string>
#include <vector>

#include "factory_maze_exporter.h"
#include "factory_maze_importer.h"
#include "matrix.h"

namespace mc {

class Maze {
 public:
  using value_type = bool;
  using MazeWallMatrix = mtlc::Matrix<value_type>;
  using size_type = MazeWallMatrix::size_type;
  using ImportType = FactoryMazeImporter::ImportType;
  using ExportType = FactoryMazeExporter::ExportType;

  enum ReturnCode {
    kCodeOk,
    kCodeInvalidSize,
    kCodeFileIsNotOpen,
    kCodeInvalidFile,
    kCodeUnderfinedFileType,
    kCodeMazeNoSolution,
    kCodeStartEndInSamePosition,
  };

  struct Point {
    int x;
    int y;
  };

  Maze();
  ~Maze();

  void SetVerticalMatrix(const MazeWallMatrix& vert_matrix);
  void SetHorizontalMatrix(const MazeWallMatrix& horiz_matrix);

  /// @brief Creates a perfect maze using the Eller algorithm
  /// @param rows Hight
  /// @param columns Weight
  /// @param rand A non-zero value disables the randomizer, each time the same
  /// algorithm will be generated for a certain number
  /// @return Return error code
  ReturnCode CreatePerfectMaze(int rows, int columns, int rand = 0);

  MazeWallMatrix GetVerticalMatrix() const;
  MazeWallMatrix GetHorizontalMatrix() const;

  /// @brief Import maze from file
  /// @param type File type
  /// @return Return error code
  ReturnCode Import(const std::string& filename, ImportType type);

  /// @brief Exprot maze from file
  /// @param type File type
  /// @return Return error code
  ReturnCode Export(const std::string& filename, ExportType type);

  size_type GetRows() const;
  size_type GetColumns() const;

  /// @brief Solves pathfinding with a wave algorithm
  /// @param points Path coordinates
  /// @return Return error code
  ReturnCode GetSolution(Point start, Point end,
                         std::vector<Point>& points) const;

 private:
  void CreateFirstLine(std::vector<int>& str_association,
                       std::map<int, int>& count_association) const;

  void MakeWallsBeforeUnion(std::vector<int>& str_association,
                            std::vector<value_type>& vertical_line) const;

  void MakeWallsAndUnion(std::vector<int>& str_association,
                         std::vector<value_type>& vertical_line,
                         std::map<int, int>& count_association);

  void ChangeLastLine(std::vector<int>& str_association,
                      std::vector<value_type>& vertical_line);

  void MakeFloor(std::vector<int>& str_association,
                 std::vector<value_type>& horizontal_line,
                 std::map<int, int>& count_association,
                 std::map<int, int>& count_walls);

  void CreateNewLine(std::vector<value_type>& horizontal_line,
                     std::vector<int>& str_association, int& max_num,
                     std::map<int, int>& count_association) const;

  bool MakeVawes(const Point& start, const Point& end, int& vawe,
                 mtlc::Matrix<int>& vawes) const;

  void MakeSolution(const Point& end, const mtlc::Matrix<int>& vawes, int vawe,
                    std::vector<Point>& points) const;

  bool TryUp(int i, int j) const;

  bool TryDown(int i, int j) const;

  bool TryLeft(int i, int j) const;

  bool TryRight(int i, int j) const;

  bool TryReturnUp(int i, int j, int vawe,
                   const mtlc::Matrix<int>& vawes) const;

  bool TryReturnDown(int i, int j, int vawe,
                     const mtlc::Matrix<int>& vawes) const;

  bool TryReturnLeft(int i, int j, int vawe,
                     const mtlc::Matrix<int>& vawes) const;

  bool TryReturnRight(int i, int j, int vawe,
                      const mtlc::Matrix<int>& vawes) const;

  bool IsEmptyCell(int i, int j, const mtlc::Matrix<int>& matrix) const;

  bool IsEndPoint(Point ref, Point exmpl) const;

  bool GoUp(const Point& end, std::stack<Point>& points,
            std::stack<Point>& new_points, mtlc::Matrix<int>& vawes,
            int vawe) const;

  bool GoDown(const Point& end, std::stack<Point>& points,
              std::stack<Point>& new_points, mtlc::Matrix<int>& vawes,
              int vawe) const;

  bool GoRight(const Point& end, std::stack<Point>& points,
               std::stack<Point>& new_points, mtlc::Matrix<int>& vawes,
               int vawe) const;

  bool GoLeft(const Point& end, std::stack<Point>& points,
              std::stack<Point>& new_points, mtlc::Matrix<int>& vawes,
              int vawe) const;

  ReturnCode ImporterCodeConvert(MazeImporter::ReturnCode code) const;

  ReturnCode ExporterCodeConvert(MazeExporter::ReturnCode code) const;

  MazeWallMatrix vertical_matrix_;

  MazeWallMatrix horizontal_matrix_;
};

}  // namespace mc

#endif  // MAZE_MODEL_MAZE_MAZE_H_
