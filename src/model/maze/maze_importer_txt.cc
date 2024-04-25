#include "maze_importer_txt.h"

#include <fstream>

#include "maze.h"
#include "token_parser.h"

namespace mc {

MazeImporterTXT::ReturnCode MazeImporterTXT::Import(const std::string& filename,
                                                    Maze& maze) {
  std::ifstream input_file(filename);
  if (input_file.fail()) return ReturnCode::kCodeFileIsNotOpen;

  std::string line;
  TokenParser::Parser token_parser;
  if (!std::getline(input_file, line)) return kCodeInvalidFile;

  token_parser.SetStr(&line);
  token_parser.SetI(0);

  TokenParser::Token token_rows = token_parser.NextInt();
  TokenParser::Token token_columns = token_parser.NextInt();
  bool token_r_state = token_rows.GetInt() > 0 &&
                       token_rows.GetInt() <=
                           static_cast<TokenParser::Token::int_type>(max_size_);
  bool token_c_state = token_columns.GetInt() > 0 &&
                       token_rows.GetInt() <=
                           static_cast<TokenParser::Token::int_type>(max_size_);
  if (!token_r_state || !token_c_state) return ReturnCode::kCodeInvalidFile;

  int rows = token_rows.GetInt();
  int columns = token_columns.GetInt();
  Maze::MazeWallMatrix vertical_matrix(rows, columns);
  int return_code =
      FillMatrix(vertical_matrix, rows, columns, token_parser, input_file);
  if (return_code != ReturnCode::kCodeOk) return ReturnCode::kCodeInvalidFile;
  maze.SetVerticalMatrix(vertical_matrix);

  Maze::MazeWallMatrix horizontal_matrix(rows, columns);
  return_code =
      FillMatrix(horizontal_matrix, rows, columns, token_parser, input_file);
  if (return_code != ReturnCode::kCodeOk) return ReturnCode::kCodeInvalidFile;
  maze.SetHorizontalMatrix(horizontal_matrix);

  return ReturnCode::kCodeOk;
}

MazeImporterTXT::ReturnCode MazeImporterTXT::FillMatrix(
    Maze::MazeWallMatrix& matrix, size_t rows, size_t columns,
    TokenParser::Parser& token_parser, std::ifstream& input_file) {
  std::string line;
  for (size_t i = 0; i < rows; ++i) {
    if (!std::getline(input_file, line)) return ReturnCode::kCodeInvalidFile;
    token_parser.SetStr(&line);
    token_parser.SetI(0);
    while (token_parser.IsEnd()) {
      if (!std::getline(input_file, line)) return ReturnCode::kCodeInvalidFile;
      token_parser.SetStr(&line);
    }

    for (size_t j = 0; j < columns; ++j) {
      TokenParser::Token token = token_parser.NextInt();
      if (token.IsNull() || (token.GetInt() != 0 && token.GetInt() != 1))
        return ReturnCode::kCodeInvalidFile;
      matrix(i, j) = token.GetInt();
    }
  }
  return ReturnCode::kCodeOk;
}

}  // namespace mc
