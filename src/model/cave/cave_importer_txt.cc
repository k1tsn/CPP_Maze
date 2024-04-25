// cave importer txt

#include "cave_importer_txt.h"

#include <fstream>
#include <string>

#include "cave.h"
#include "cave_importer.h"
#include "string_parser.h"

namespace mc {

CaveImporterTXT::CaveImporterTXT() {}

CaveImporterTXT::~CaveImporterTXT() {}

CaveImporterTXT::ReturnCode CaveImporterTXT::Import(const std::string& filename,
                                                    Cave& cave) {
  std::ifstream file(filename);
  if (file.fail()) return kCodeFileDontOpen;

  TokenParser::StringParser token_parser;
  std::string str;
  if (!std::getline(file, str)) return kCodeInvalidFile;

  token_parser.SetStr(&str);
  token_parser.SetI(0);

  TokenParser::Token token_w = token_parser.NextInt();
  TokenParser::Token token_h = token_parser.NextInt();
  bool token_w_ok = token_w.IsInt() && token_w.GetInt() >= 1;
  bool token_h_ok = token_h.IsInt() && token_h.GetInt() >= 1;
  if (!token_w_ok || !token_h_ok) return kCodeInvalidFile;

  auto w = static_cast<Cave::size_type>(token_w.GetInt());
  auto h = static_cast<Cave::size_type>(token_h.GetInt());
  Cave::CaveMatrix matrix(w, h);
  for (Cave::size_type i = Cave::size_type(0); i < matrix.GetRows(); ++i) {
    if (!std::getline(file, str)) return kCodeInvalidFile;
    token_parser.SetStr(&str);
    token_parser.SetI(0);

    for (Cave::size_type j = Cave::size_type(0); j < matrix.GetCols(); ++j) {
      TokenParser::Token token = token_parser.NextInt();
      if (!token.IsInt() || (token.GetInt() != 0 && token.GetInt() != 1))
        return kCodeInvalidFile;
      matrix(i, j) = (token.GetInt() == 0 ? false : true);
    }
  }

  cave.SetMatrix(matrix);
  return kCodeOk;
}

}  // namespace mc
