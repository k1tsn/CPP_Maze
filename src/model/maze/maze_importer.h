#ifndef MAZE_MODEL_MAZE_MAZE_IMPORTER_H_
#define MAZE_MODEL_MAZE_MAZE_IMPORTER_H_

#include <string>

namespace mc {

class Maze;

class MazeImporter {
 public:
  enum ReturnCode {
    kCodeOk,
    kCodeFileIsNotOpen,
    kCodeInvalidFile,
    kCodeUnderfinedFileType
  };

  MazeImporter() {}
  virtual ~MazeImporter() {}

  virtual ReturnCode Import(const std::string& filename, Maze& maze) = 0;
};

}  // namespace mc

#endif  // MAZE_MODEL_MAZE_MAZE_IMPORTER_H_
