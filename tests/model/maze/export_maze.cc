#include <gtest/gtest.h>

#include <string>

#include "../../../src/model/maze/maze.h"
#include "matrix.h"

struct ExportMazeData {
  mc::Maze::ReturnCode create_maze_code_;
  mc::Maze::ReturnCode export_code_;
  mc::Maze::ExportType export_type_;
  std::string filename_;
  int rows_;
  int columns_;
};

class ExportMaze : public testing::TestWithParam<int> {
 public:
  static int count_;
  static std::vector<ExportMazeData> test_data_;
};

int ExportMaze::count_ = 3;
std::vector<ExportMazeData> ExportMaze::test_data_ = {
    ExportMazeData{mc::Maze::ReturnCode::kCodeOk, mc::Maze::ReturnCode::kCodeOk,
                   mc::Maze::ExportType::kTypeTXT,
                   "datasets/maze/.maze_test_export.txt", 14, 14},
    ExportMazeData{mc::Maze::ReturnCode::kCodeOk,
                   mc::Maze::ReturnCode::kCodeUnderfinedFileType,
                   static_cast<mc::Maze::ExportType>(10),
                   "datasets/maze/.maze_test_export.txt", 14, 14},
    ExportMazeData{mc::Maze::ReturnCode::kCodeOk,
                   mc::Maze::ReturnCode::kCodeFileIsNotOpen,
                   mc::Maze::ExportType::kTypeTXT, "/", 14, 14}};

INSTANTIATE_TEST_SUITE_P(export_maze_data, ExportMaze,
                         testing::Range(0, ExportMaze::count_));

TEST_P(ExportMaze, ExportMaze) {
  int num_test = this->GetParam();
  ExportMazeData& test_data = ExportMaze::test_data_[num_test];

  mc::Maze maze;

  mc::Maze::ReturnCode code =
      maze.CreatePerfectMaze(test_data.rows_, test_data.columns_);

  ASSERT_EQ(code, test_data.create_maze_code_);

  code = maze.Export(test_data.filename_, test_data.export_type_);

  ASSERT_EQ(code, test_data.export_code_);
}
