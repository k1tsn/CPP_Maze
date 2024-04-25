#ifndef MAZE_MODEL_MAZE_MAZE_EXPORTER_TXT_H_
#define MAZE_MODEL_MAZE_MAZE_EXPORTER_TXT_H_

#include <string>

#include "maze.h"
#include "maze_exporter.h"

namespace mc {

class MazeExporterTXT : public MazeExporter {
 public:
  using ReturnCode = MazeExporter::ReturnCode;

  MazeExporterTXT() {}
  virtual ~MazeExporterTXT() {}

  ReturnCode Export(const std::string& filename, const Maze& maze) override;

 private:
  void ExportMatrix(const Maze::MazeWallMatrix& matrix, std::ofstream& out);
};

}  // namespace mc

#endif  // MAZE_MODEL_MAZE_MAZE_EXPORTER_H_
