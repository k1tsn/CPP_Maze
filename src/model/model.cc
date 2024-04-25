// fasade model

#include "model.h"

#include <string>
#include <vector>

#include "cave/cave.h"
#include "maze/maze.h"

namespace mc {

Model::Model() {}

Model::~Model() {}

// ------------------------------------------------------------------------- //
//                                  Maze                                     //
// ------------------------------------------------------------------------- //

Model::ReturnCode Model::MazeImport(const std::string& filename) {
  Maze::ReturnCode code = maze_.Import(filename, Maze::ImportType::kTypeTXT);
  return MazeCodeConvert(code);
}

Model::ReturnCode Model::MazeExport(const std::string& filename) {
  Maze::ReturnCode code = maze_.Export(filename, Maze::ExportType::kTypeTXT);
  return MazeCodeConvert(code);
}

Model::ReturnCode Model::CreatePerfectMaze(size_type rows, size_type columns,
                                           int rand) {
  Maze::ReturnCode code = maze_.CreatePerfectMaze(rows, columns, rand);
  return MazeCodeConvert(code);
}

Model::ReturnCode Model::GetSolutionMaze(Point start, Point end,
                                         std::vector<Point>& points) {
  Maze::ReturnCode code = maze_.GetSolution(start, end, points);
  return MazeCodeConvert(code);
}

Model::size_type Model::GetWidthMaze() { return maze_.GetColumns(); }

Model::size_type Model::GetHeightMaze() { return maze_.GetRows(); }

Model::MazeWallMatrix Model::GetVerticalWallsMaze() {
  return maze_.GetVerticalMatrix();
}

Model::MazeWallMatrix Model::GetHorisontalWallsMaze() {
  return maze_.GetHorizontalMatrix();
}

// ------------------------------------------------------------------------- //
//                                  Cave                                     //
// ------------------------------------------------------------------------- //

Model::ReturnCode Model::CaveImport(const std::string& filename) {
  Cave::ReturnCode code = cave_.Import(filename, Cave::ImportType::kTypeTXT);
  return CaveCodeConvert(code);
}

Model::ReturnCode Model::CaveExport(const std::string& filename) const {
  Cave::ReturnCode code = cave_.Export(filename, Cave::ExportType::kTypeTXT);
  return CaveCodeConvert(code);
}

Model::ReturnCode Model::CaveSetRandom(int chance, int w, int h) {
  Cave::ReturnCode code = cave_.SetRandom(chance, w, h);
  return CaveCodeConvert(code);
}

Model::ReturnCode Model::CaveNextIteration(int birth_limit, int death_limit) {
  Cave::ReturnCode code = cave_.NextIteration(birth_limit, death_limit);
  return CaveCodeConvert(code);
}

Model::size_type Model::GetWidthCave() const {
  return static_cast<size_type>(cave_.GetWidth());
}

Model::size_type Model::GetHeightCave() const {
  return static_cast<size_type>(cave_.GetHeight());
}

Model::CaveMatrix Model::GetCaveMatrix() const { return cave_.GetMatrix(); }

// ------------------------------------------------------------------------- //
//                                  Utils                                    //
// ------------------------------------------------------------------------- //

Model::ReturnCode Model::MazeCodeConvert(Maze::ReturnCode code) {
  switch (code) {
    case Maze::ReturnCode::kCodeInvalidSize:
      return ReturnCode::kCodeInvalidSizeGiven;
      break;

    case Maze::ReturnCode::kCodeFileIsNotOpen:
      return ReturnCode::kCodeFileDontOpen;
      break;

    case Maze::ReturnCode::kCodeInvalidFile:
      return ReturnCode::kCodeInvalidFile;
      break;

    case Maze::ReturnCode::kCodeUnderfinedFileType:
      return ReturnCode::kCodeUnderfinedFileType;
      break;

    case Maze::ReturnCode::kCodeMazeNoSolution:
      return ReturnCode::kCodeMazeNoSolution;
      break;

    case Maze::ReturnCode::kCodeStartEndInSamePosition:
      return ReturnCode::kCodeStartEndInSamePosition;
      break;

    default:
      break;
  }
  return ReturnCode::kCodeOk;
}

Model::ReturnCode Model::CaveCodeConvert(Cave::ReturnCode code) {
  switch (code) {
    case Cave::ReturnCode::kCodeFileDontOpen:
      return ReturnCode::kCodeFileDontOpen;
      break;

    case Cave::ReturnCode::kCodeFileDontSave:
      return ReturnCode::kCodeFileDontOpen;
      break;

    case Cave::ReturnCode::kCodeInvalidfile:
      return ReturnCode::kCodeInvalidFile;
      break;

    case Cave::ReturnCode::kCodeInvData:
      return ReturnCode::kCodeInvalidData;
      break;

    case Cave::ReturnCode::kCodeGenerationNotChange:
      return ReturnCode::kCodeCaveNextGenNotChange;
      break;

    default:
      break;
  }
  return ReturnCode::kCodeOk;
}

}  // namespace mc
