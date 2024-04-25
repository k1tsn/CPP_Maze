#include "maze_exporter_txt.h"

#include <fstream>

namespace mc {

MazeExporterTXT::ReturnCode MazeExporterTXT::Export(const std::string& filename,
                                                    const Maze& maze) {
  std::ofstream out(filename);
  if (out.fail()) return ReturnCode::kCodeFileIsNotOpen;

  Maze::MazeWallMatrix vertical_matrix = maze.GetVerticalMatrix();
  Maze::MazeWallMatrix horizontal_matrix = maze.GetHorizontalMatrix();

  out << vertical_matrix.GetRows() << " " << vertical_matrix.GetCols()
      << std::endl;

  ExportMatrix(vertical_matrix, out);

  out << std::endl;

  ExportMatrix(horizontal_matrix, out);

  return ReturnCode::kCodeOk;
}

void MazeExporterTXT::ExportMatrix(const Maze::MazeWallMatrix& matrix,
                                   std::ofstream& out) {
  for (int i = 0; i < int(matrix.GetRows()); ++i) {
    for (int j = 0; j < int(matrix.GetCols()); ++j) {
      out << matrix(i, j) << " ";
    }
    out << std::endl;
  }
}

}  // namespace mc
