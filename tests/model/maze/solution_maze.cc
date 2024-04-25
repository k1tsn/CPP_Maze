#include <gtest/gtest.h>

#include <string>

#include "../../../src/model/maze/maze.h"
#include "matrix.h"

struct SolutionMazeData {
  mc::Maze::ImportType import_type_;
  mc::Maze::ReturnCode code_import_;
  mc::Maze::ReturnCode code_;
  std::string filename_;
  mc::Maze::Point start_;
  mc::Maze::Point end_;
  std::vector<mc::Maze::Point> solution_;
};

class SolutionMaze : public testing::TestWithParam<int> {
 public:
  static int count_;
  static std::vector<SolutionMazeData> test_data_;
};

int SolutionMaze::count_ = 8;
std::vector<SolutionMazeData> SolutionMaze::test_data_ = {
    SolutionMazeData{mc::Maze::ImportType::kTypeTXT,
                     mc::Maze::ReturnCode::kCodeOk,
                     mc::Maze::ReturnCode::kCodeOk,
                     "datasets/maze/maze1_loop.txt",
                     {2, 2},
                     {4, 4},
                     {{4, 4}, {4, 3}, {3, 3}, {3, 2}, {2, 2}}},
    SolutionMazeData{
        mc::Maze::ImportType::kTypeTXT,
        mc::Maze::ReturnCode::kCodeOk,
        mc::Maze::ReturnCode::kCodeOk,
        "datasets/maze/maze2_loop.txt",
        {6, 2},
        {3, 6},
        {{3, 6}, {3, 5}, {3, 4}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {6, 2}}},
    SolutionMazeData{mc::Maze::ImportType::kTypeTXT,
                     mc::Maze::ReturnCode::kCodeOk,
                     mc::Maze::ReturnCode::kCodeOk,
                     "datasets/maze/maze2_loop.txt",
                     {5, 2},
                     {7, 2},
                     {{7, 2}, {6, 2}, {6, 3}, {5, 3}, {5, 2}}},
    SolutionMazeData{mc::Maze::ImportType::kTypeTXT,
                     mc::Maze::ReturnCode::kCodeOk,
                     mc::Maze::ReturnCode::kCodeOk,
                     "datasets/maze/maze2_loop.txt",
                     {1, 1},
                     {0, 0},
                     {{0, 0}, {1, 0}, {1, 1}}},
    SolutionMazeData{mc::Maze::ImportType::kTypeTXT,
                     mc::Maze::ReturnCode::kCodeOk,
                     mc::Maze::ReturnCode::kCodeMazeNoSolution,
                     "datasets/maze/maze3_isolated_area.txt",
                     {0, 3},
                     {5, 0},
                     {}},
    SolutionMazeData{mc::Maze::ImportType::kTypeTXT,
                     mc::Maze::ReturnCode::kCodeOk,
                     mc::Maze::ReturnCode::kCodeStartEndInSamePosition,
                     "datasets/maze/maze3_isolated_area.txt",
                     {5, 0},
                     {5, 0},
                     {}},
    SolutionMazeData{
        mc::Maze::ImportType::kTypeTXT,
        mc::Maze::ReturnCode::kCodeOk,
        mc::Maze::ReturnCode::kCodeOk,
        "datasets/maze/maze4_empty.txt",
        {3, 4},
        {7, 1},
        {{7, 1}, {7, 2}, {7, 3}, {7, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 4}}},
    SolutionMazeData{mc::Maze::ImportType::kTypeTXT,
                     mc::Maze::ReturnCode::kCodeOk,
                     mc::Maze::ReturnCode::kCodeOk,
                     "datasets/maze/maze4_empty.txt",
                     {7, 7},
                     {1, 1},
                     {{1, 1},
                      {1, 2},
                      {1, 3},
                      {1, 4},
                      {1, 5},
                      {1, 6},
                      {1, 7},
                      {2, 7},
                      {3, 7},
                      {4, 7},
                      {5, 7},
                      {6, 7},
                      {7, 7}}}};

INSTANTIATE_TEST_SUITE_P(maze_data, SolutionMaze,
                         testing::Range(0, SolutionMaze::count_));

TEST_P(SolutionMaze, Solution) {
  int num_test = this->GetParam();
  SolutionMazeData& test_data = SolutionMaze::test_data_[num_test];

  mc::Maze maze;

  mc::Maze::ReturnCode code =
      maze.Import(test_data.filename_, test_data.import_type_);
  ASSERT_EQ(test_data.code_import_, code);

  std::vector<mc::Maze::Point> solution;
  code = maze.GetSolution(test_data.start_, test_data.end_, solution);

  ASSERT_EQ(test_data.code_, code);

  if (code == mc::Maze::ReturnCode::kCodeOk) {
    for (size_t i = 0; i < solution.size(); ++i) {
      ASSERT_EQ(solution[i].x, test_data.solution_[i].x);
      ASSERT_EQ(solution[i].y, test_data.solution_[i].y);
    }
  }
}
