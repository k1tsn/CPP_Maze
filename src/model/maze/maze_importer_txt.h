#ifndef MAZE_MODEL_MAZE_IMPORTER_TXT_H_
#define MAZE_MODEL_MAZE_IMPORTER_TXT_H_

#include <string>

#include "maze.h"
#include "maze_importer.h"
#include "token_parser.h"

namespace mc {

class MazeImporterTXT : public MazeImporter {
 public:
  using ReturnCode = MazeImporter::ReturnCode;

  MazeImporterTXT() {}
  virtual ~MazeImporterTXT() {}

  ReturnCode Import(const std::string& filename, Maze& maze) override;

 private:
  ReturnCode FillMatrix(Maze::MazeWallMatrix& matrix, size_t rows,
                        size_t columns, TokenParser::Parser& token_parser,
                        std::ifstream& input_file);

  const size_t max_size_ = 50;
};

}  // namespace mc

#endif  // MAZE_MODEL_MAZE_IMPORTER_H_
