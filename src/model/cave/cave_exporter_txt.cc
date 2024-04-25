// cave exporter txt

#include "cave_exporter_txt.h"

#include <fstream>
#include <string>

#include "cave.h"
#include "cave_exporter.h"

namespace mc {

CaveExporterTXT::CaveExporterTXT() : CaveExporter() {}

CaveExporterTXT::~CaveExporterTXT() {}

CaveExporterTXT::ReturnCode CaveExporterTXT::Export(
    const Cave& cave, const std::string& filename) {
  std::ofstream file(filename);
  if (file.fail()) return kCodeFileDontSave;

  file << cave.GetHeight() << " " << cave.GetWidth() << "\n";

  const Cave::CaveMatrix& mat = cave.GetMatrix();
  for (Cave::size_type i = Cave::size_type(0); i < mat.GetRows(); ++i) {
    Cave::size_type j = Cave::size_type(0);
    for (; j < cave.GetMatrix().GetCols() - 1; ++j)
      file << static_cast<int>(cave.GetMatrix()(i, j)) << " ";
    file << static_cast<int>(cave.GetMatrix()(i, j)) << "\n";
  }

  return kCodeOk;
}

}  // namespace mc
