// controller default

#include "controller_default.h"

#include <string>

#include "controller.h"
#include "model/model.h"

namespace mc {

ControllerDefault::ControllerDefault(Model* model)
    : Controller(), model_(model) {}

ControllerDefault::~ControllerDefault() {}

// ------------------------------------------------------------------------- //
//                                  Maze                                     //
// ------------------------------------------------------------------------- //

ControllerDefault::ReturnCode ControllerDefault::MazeImport(
    const std::string& filename) {
  return model_->MazeImport(filename);
}

ControllerDefault::ReturnCode ControllerDefault::MazeExport(
    const std::string& filename) {
  return model_->MazeExport(filename);
}

ControllerDefault::ReturnCode ControllerDefault::GenIdealMaze(
    size_type width, size_type height) {
  return model_->CreatePerfectMaze(height, width);
}

ControllerDefault::ReturnCode ControllerDefault::GetSolutionMaze(
    Point start, Point end, std::vector<Point>& points) {
  return model_->GetSolutionMaze(start, end, points);
}

ControllerDefault::size_type ControllerDefault::GetWidthMaze() {
  return model_->GetWidthMaze();
}

ControllerDefault::size_type ControllerDefault::GetHeightMaze() {
  return model_->GetHeightMaze();
}

ControllerDefault::MazeWallMatrix ControllerDefault::GetVerticalWallsMaze() {
  return model_->GetVerticalWallsMaze();
}

ControllerDefault::MazeWallMatrix ControllerDefault::GetHorisontalWallsMaze() {
  return model_->GetHorisontalWallsMaze();
}

// ------------------------------------------------------------------------- //
//                                  Cave                                     //
// ------------------------------------------------------------------------- //

ControllerDefault::ReturnCode ControllerDefault::CaveImport(
    const std::string& filename) {
  return model_->CaveImport(filename);
}

ControllerDefault::ReturnCode ControllerDefault::CaveExport(
    const std::string& filename) const {
  return model_->CaveExport(filename);
}

ControllerDefault::ReturnCode ControllerDefault::CaveSetRandom(int chance,
                                                               int w, int h) {
  return model_->CaveSetRandom(chance, w, h);
}

ControllerDefault::ReturnCode ControllerDefault::CaveNextIteration(
    int birth_limit, int death_limit) {
  return model_->CaveNextIteration(birth_limit, death_limit);
}

ControllerDefault::size_type ControllerDefault::GetWidthCave() const {
  return model_->GetWidthCave();
}

ControllerDefault::size_type ControllerDefault::GetHeightCave() const {
  return model_->GetHeightCave();
}

ControllerDefault::CaveMatrix ControllerDefault::GetCaveMatrix() const {
  return model_->GetCaveMatrix();
}

}  // namespace mc
