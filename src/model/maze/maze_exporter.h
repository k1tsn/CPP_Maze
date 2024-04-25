#ifndef MAZE_MODEL_MAZE_MAZE_EXPORTER_H_
#define MAZE_MODEL_MAZE_MAZE_EXPORTER_H_

#include <string>

namespace mc {

class Maze;

class MazeExporter {
 public:
  enum ReturnCode {
    kCodeOk,
    kCodeFileIsNotOpen,
    kCodeInvalidFile,
    kCodeUnderfinedFileType
  };

  MazeExporter() {}
  virtual ~MazeExporter() {}

  virtual ReturnCode Export(const std::string& filename, const Maze& maze) = 0;
};

}  // namespace mc

#endif  // MAZE_MODEL_MAZE_MAZE_EXPORTER_H_
