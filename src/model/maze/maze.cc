#include "maze.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

#include "factory_maze_exporter.h"
#include "factory_maze_importer.h"
#include "maze_exporter.h"
#include "maze_importer.h"

namespace mc {

Maze::Maze() {}

Maze::~Maze() {}

Maze::ReturnCode Maze::Import(const std::string& filename, ImportType type) {
  FactoryMazeImporter factory;
  MazeImporter* import = factory.Create(type);
  if (import == nullptr) return Maze::ReturnCode::kCodeUnderfinedFileType;

  MazeImporter::ReturnCode code = import->Import(filename, *this);

  delete import;
  return ImporterCodeConvert(code);
}

Maze::ReturnCode Maze::Export(const std::string& filename, ExportType type) {
  FactoryMazeExporter factory;
  MazeExporter* maze_export = factory.Create(type);
  if (maze_export == nullptr) return Maze::ReturnCode::kCodeUnderfinedFileType;

  MazeExporter::ReturnCode code = maze_export->Export(filename, *this);

  delete maze_export;
  return ExporterCodeConvert(code);
}

void Maze::SetVerticalMatrix(const mtlc::Matrix<value_type>& vert_matrix) {
  vertical_matrix_ = vert_matrix;
}

void Maze::SetHorizontalMatrix(const mtlc::Matrix<value_type>& horiz_matrix) {
  horizontal_matrix_ = horiz_matrix;
}

Maze::ReturnCode Maze::GetSolution(Point start, Point end,
                                   std::vector<Point>& points) const {
  points.clear();
  if (start.x == end.x && start.y == end.y)
    return ReturnCode::kCodeStartEndInSamePosition;

  int rows = horizontal_matrix_.GetRows();
  int columns = horizontal_matrix_.GetCols();

  mtlc::Matrix<int> vawes(rows, columns);
  vawes(start.y, start.x) = -1;
  int vawe = 1;

  bool is_solution = MakeVawes(start, end, vawe, vawes);

  if (!is_solution) {
    return ReturnCode::kCodeMazeNoSolution;
  }

  MakeSolution(end, vawes, vawe, points);

  return ReturnCode::kCodeOk;
}

void Maze::MakeSolution(const Point& end, const mtlc::Matrix<int>& vawes,
                        int vawe, std::vector<Point>& points) const {
  Point return_way = end;
  points.push_back(return_way);
  int count_way = vawe;
  for (int i = 2; i < count_way + 2; ++i, --vawe) {
    if (TryReturnUp(return_way.y, return_way.x, vawe, vawes))
      --return_way.y;
    else if (TryReturnDown(return_way.y, return_way.x, vawe, vawes))
      ++return_way.y;
    else if (TryReturnLeft(return_way.y, return_way.x, vawe, vawes))
      --return_way.x;
    else if (TryReturnRight(return_way.y, return_way.x, vawe, vawes))
      ++return_way.x;
    points.push_back(return_way);
  }
}

bool Maze::MakeVawes(const Point& start, const Point& end, int& vawe,
                     mtlc::Matrix<int>& vawes) const {
  std::stack<Point> points;
  points.push(start);

  while (!points.empty()) {
    std::stack<Point> new_points;
    while (!points.empty()) {
      if (TryUp(points.top().y, points.top().x)) {
        bool is_end = GoUp(end, points, new_points, vawes, vawe);
        if (is_end) return true;
      }
      if (TryDown(points.top().y, points.top().x)) {
        bool is_end = GoDown(end, points, new_points, vawes, vawe);
        if (is_end) return true;
      }
      if (TryLeft(points.top().y, points.top().x)) {
        bool is_end = GoLeft(end, points, new_points, vawes, vawe);
        if (is_end) return true;
      }
      if (TryRight(points.top().y, points.top().x)) {
        bool is_end = GoRight(end, points, new_points, vawes, vawe);
        if (is_end) return true;
      }
      points.pop();
    }
    ++vawe;
    points.swap(new_points);
  }

  return false;
}

bool Maze::TryUp(int i, int j) const {
  if (i - 1 >= 0) {
    if (horizontal_matrix_(i - 1, j) == 0) return true;
  }
  return false;
}

bool Maze::TryDown(int i, int j) const {
  if (i + 1 < int(horizontal_matrix_.GetRows())) {
    if (horizontal_matrix_(i, j) == 0) return true;
  }
  return false;
}

bool Maze::TryLeft(int i, int j) const {
  if (j - 1 >= 0) {
    if (vertical_matrix_(i, j - 1) == 0) return true;
  }
  return false;
}

bool Maze::TryRight(int i, int j) const {
  if (j + 1 < int(vertical_matrix_.GetCols())) {
    if (vertical_matrix_(i, j) == 0) return true;
  }
  return false;
}

bool Maze::GoUp(const Point& end, std::stack<Point>& points,
                std::stack<Point>& new_points, mtlc::Matrix<int>& vawes,
                int vawe) const {
  Point up = {points.top().x, points.top().y - 1};
  if (IsEndPoint(end, up)) {
    vawes(points.top().y - 1, points.top().x) = vawe;
    return true;
  }
  if (IsEmptyCell(points.top().y - 1, points.top().x, vawes)) {
    vawes(points.top().y - 1, points.top().x) = vawe;
    new_points.push(up);
  }
  return false;
}

bool Maze::GoDown(const Point& end, std::stack<Point>& points,
                  std::stack<Point>& new_points, mtlc::Matrix<int>& vawes,
                  int vawe) const {
  Point down = {points.top().x, points.top().y + 1};
  if (IsEndPoint(end, down)) {
    vawes(points.top().y + 1, points.top().x) = vawe;
    return true;
  }
  if (IsEmptyCell(points.top().y + 1, points.top().x, vawes)) {
    vawes(points.top().y + 1, points.top().x) = vawe;
    new_points.push(down);
  }
  return false;
}

bool Maze::GoRight(const Point& end, std::stack<Point>& points,
                   std::stack<Point>& new_points, mtlc::Matrix<int>& vawes,
                   int vawe) const {
  Point right = {points.top().x + 1, points.top().y};
  if (IsEndPoint(end, right)) {
    vawes(points.top().y, points.top().x + 1) = vawe;
    return true;
  }
  if (IsEmptyCell(points.top().y, points.top().x + 1, vawes)) {
    vawes(points.top().y, points.top().x + 1) = vawe;
    new_points.push(right);
  }
  return false;
}

bool Maze::GoLeft(const Point& end, std::stack<Point>& points,
                  std::stack<Point>& new_points, mtlc::Matrix<int>& vawes,
                  int vawe) const {
  Point left = {points.top().x - 1, points.top().y};
  if (IsEndPoint(end, left)) {
    vawes(points.top().y, points.top().x - 1) = vawe;
    return true;
  }
  if (IsEmptyCell(points.top().y, points.top().x - 1, vawes)) {
    vawes(points.top().y, points.top().x - 1) = vawe;
    new_points.push(left);
  }
  return false;
}

bool Maze::TryReturnUp(int i, int j, int vawe,
                       const mtlc::Matrix<int>& vawes) const {
  if (i - 1 >= 0 && TryUp(i, j)) {
    if ((vawes(i - 1, j) == vawe - 1 && vawes(i - 1, j) != 0) ||
        (vawes(i - 1, j) == -1))
      return true;
  }
  return false;
}

bool Maze::TryReturnDown(int i, int j, int vawe,
                         const mtlc::Matrix<int>& vawes) const {
  if (i + 1 < int(vawes.GetRows()) && TryDown(i, j)) {
    if ((vawes(i + 1, j) == vawe - 1 && vawes(i + 1, j) != 0) ||
        (vawes(i + 1, j) == -1))
      return true;
  }
  return false;
}

bool Maze::TryReturnLeft(int i, int j, int vawe,
                         const mtlc::Matrix<int>& vawes) const {
  if (j - 1 >= 0 && TryLeft(i, j)) {
    if ((vawes(i, j - 1) == vawe - 1 && vawes(i, j - 1) != 0) ||
        (vawes(i, j - 1) == -1))
      return true;
  }
  return false;
}

bool Maze::TryReturnRight(int i, int j, int vawe,
                          const mtlc::Matrix<int>& vawes) const {
  if (j + 1 < int(vawes.GetCols()) && TryRight(i, j)) {
    if ((vawes(i, j + 1) == vawe - 1 && vawes(i, j + 1) != 0) ||
        (vawes(i, j + 1) == -1))
      return true;
  }
  return false;
}

bool Maze::IsEmptyCell(int i, int j, const mtlc::Matrix<int>& matrix) const {
  return matrix(i, j) == 0;
}

bool Maze::IsEndPoint(Point ref, Point exmpl) const {
  return ref.x == exmpl.x && ref.y == exmpl.y;
}

Maze::ReturnCode Maze::CreatePerfectMaze(int rows, int columns, int rand) {
  if (rows > 50 || rows <= 0) return ReturnCode::kCodeInvalidSize;
  if (columns > 50 || columns <= 0) return ReturnCode::kCodeInvalidSize;

  vertical_matrix_.SetRows(rows);
  vertical_matrix_.SetCols(columns);
  horizontal_matrix_.SetRows(rows);
  horizontal_matrix_.SetCols(columns);

  std::srand(std::time(nullptr));
  if (rand != 0) std::srand(rand);

  std::map<int, int> count_association;
  std::vector<int> str_association(columns);
  CreateFirstLine(str_association, count_association);

  int max_num = str_association[columns - 1];

  for (int line = 0; line < rows; ++line) {
    std::vector<value_type> vertical_line(columns);
    MakeWallsBeforeUnion(str_association, vertical_line);

    MakeWallsAndUnion(str_association, vertical_line, count_association);

    if (line == rows - 1) {
      ChangeLastLine(str_association, vertical_line);
    }

    for (int i = 0; i < columns; ++i)
      vertical_matrix_(line, i) = vertical_line[i];

    std::map<int, int> count_walls = count_association;
    for (auto iter = count_walls.begin(); iter != count_walls.end(); ++iter) {
      iter->second = 0;
    }

    std::vector<value_type> horizontal_line(columns);
    MakeFloor(str_association, horizontal_line, count_association, count_walls);

    for (int i = 0; i < columns; ++i)
      horizontal_matrix_(line, i) = horizontal_line[i];

    CreateNewLine(horizontal_line, str_association, max_num, count_association);
  }

  for (int i = 0; i < columns; ++i) horizontal_matrix_(rows - 1, i) = 1;

  return ReturnCode::kCodeOk;
}

void Maze::CreateFirstLine(std::vector<int>& str_association,
                           std::map<int, int>& count_association) const {
  for (int i = 0; i < int(str_association.size()); ++i) {
    str_association[i] = i + 1;
    count_association.insert({str_association[i], 1});
  }
}

void Maze::MakeWallsBeforeUnion(std::vector<int>& str_association,
                                std::vector<value_type>& vertical_line) const {
  for (int i = 0; i < int(str_association.size()) - 1; ++i) {
    if (str_association[i] == str_association[i + 1]) {
      vertical_line[i] = 1;
    }
  }
}

void Maze::MakeWallsAndUnion(std::vector<int>& str_association,
                             std::vector<value_type>& vertical_line,
                             std::map<int, int>& count_association) {
  for (int i = 0; i < int(vertical_line.size()) - 1; ++i) {
    bool put_up_a_wall = rand() % 2;
    if (put_up_a_wall) {
      vertical_line[i] = 1;
    } else {
      if (str_association[i] == str_association[i + 1]) {
        vertical_line[i] = 1;
      } else {
        int ref = str_association[i + 1];
        for (int j = 0; j < int(vertical_line.size()); ++j) {
          if (str_association[j] == ref) {
            std::map<int, int>::iterator iter =
                count_association.find(str_association[i]);
            ++iter->second;
            count_association.erase(str_association[j]);
            str_association[j] = str_association[i];
          }
        }
      }
    }
  }
  vertical_line[int(vertical_line.size()) - 1] = 1;
}

void Maze::ChangeLastLine(std::vector<int>& str_association,
                          std::vector<value_type>& vertical_line) {
  for (int i = 0; i < int(vertical_line.size()) - 1; ++i) {
    if (str_association[i] != str_association[i + 1] && vertical_line[i] == 1) {
      vertical_line[i] = 0;
      int ref = str_association[i + 1];
      for (int j = 0; j < int(str_association.size()); ++j) {
        if (str_association[j] == ref) str_association[j] = str_association[i];
      }
    }
  }
}

void Maze::MakeFloor(std::vector<int>& str_association,
                     std::vector<value_type>& horizontal_line,
                     std::map<int, int>& count_association,
                     std::map<int, int>& count_walls) {
  for (int i = 0; i < int(horizontal_line.size()); ++i) {
    std::map<int, int>::iterator iter_count =
        count_association.find(str_association[i]);
    std::map<int, int>::iterator iter_putted_wall =
        count_walls.find(str_association[i]);
    if (iter_count->second > 1 &&
        iter_putted_wall->second < iter_count->second - 1) {
      bool put_up_a_wall = rand() % 2;
      if (put_up_a_wall) {
        horizontal_line[i] = 1;
        ++iter_putted_wall->second;
      }
    }
  }
}

void Maze::CreateNewLine(std::vector<value_type>& horizontal_line,
                         std::vector<int>& str_association, int& max_num,
                         std::map<int, int>& count_association) const {
  for (int i = 0; i < int(horizontal_line.size()); ++i) {
    if (horizontal_line[i] == 1) {
      std::map<int, int>::iterator iter =
          count_association.find(str_association[i]);
      --iter->second;
      str_association[i] = max_num + 1;
      count_association.insert({str_association[i], 1});
      max_num = str_association[i];
    }
  }
}

mtlc::Matrix<Maze::value_type> Maze::GetVerticalMatrix() const {
  return vertical_matrix_;
}

mtlc::Matrix<Maze::value_type> Maze::GetHorizontalMatrix() const {
  return horizontal_matrix_;
}

Maze::size_type Maze::GetRows() const { return vertical_matrix_.GetRows(); }

Maze::size_type Maze::GetColumns() const { return vertical_matrix_.GetCols(); }

Maze::ReturnCode Maze::ImporterCodeConvert(
    MazeImporter::ReturnCode code) const {
  switch (code) {
    case MazeImporter::ReturnCode::kCodeFileIsNotOpen:
      return ReturnCode::kCodeFileIsNotOpen;
      break;

    case MazeImporter::ReturnCode::kCodeInvalidFile:
      return ReturnCode::kCodeInvalidFile;
      break;

    default:
      break;
  }
  return ReturnCode::kCodeOk;
}

Maze::ReturnCode Maze::ExporterCodeConvert(
    MazeExporter::ReturnCode code) const {
  switch (code) {
    case MazeExporter::ReturnCode::kCodeFileIsNotOpen:
      return ReturnCode::kCodeFileIsNotOpen;
      break;

    default:
      break;
  }
  return ReturnCode::kCodeOk;
}

}  // namespace mc
