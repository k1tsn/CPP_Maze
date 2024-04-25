#include <gtest/gtest.h>

#include <string>

#include "../../../src/model/maze/maze.h"
#include "matrix.h"

struct ImportMazeData {
  mc::Maze::ReturnCode import_code_;
  mc::Maze::ImportType import_type_;
  std::string filename_;
};

class ImportMaze : public testing::TestWithParam<int> {
 public:
  static int count_;
  static std::vector<ImportMazeData> test_data_;
};

int ImportMaze::count_ = 3;
std::vector<ImportMazeData> ImportMaze::test_data_ = {
    ImportMazeData{mc::Maze::ReturnCode::kCodeInvalidFile,
                   mc::Maze::ImportType::kTypeTXT,
                   "datasets/maze/maze5_invalid_data.txt"},
    ImportMazeData{mc::Maze::ReturnCode::kCodeUnderfinedFileType,
                   static_cast<mc::Maze::ImportType>(10), ""},
    ImportMazeData{mc::Maze::ReturnCode::kCodeFileIsNotOpen,
                   mc::Maze::ImportType::kTypeTXT, "d"}};

INSTANTIATE_TEST_SUITE_P(import_maze_data, ImportMaze,
                         testing::Range(0, ImportMaze::count_));

TEST_P(ImportMaze, ImportMaze) {
  int num_test = this->GetParam();
  ImportMazeData& test_data = ImportMaze::test_data_[num_test];

  mc::Maze maze;

  mc::Maze::ReturnCode code =
      maze.Import(test_data.filename_, test_data.import_type_);

  ASSERT_EQ(code, test_data.import_code_);
}
