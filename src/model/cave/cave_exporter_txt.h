// cave exporter txt

#ifndef MAZE_MODEL_CAVE_CAVE_EXPORTER_TXT_H_
#define MAZE_MODEL_CAVE_CAVE_EXPORTER_TXT_H_

#include <string>

#include "cave.h"
#include "cave_exporter.h"

namespace mc {

class CaveExporterTXT : public CaveExporter {
 public:
  using ReturnCode = CaveExporter::ReturnCode;

  CaveExporterTXT();
  virtual ~CaveExporterTXT();

  /// @brief Export cave into file
  /// @return kCodeOk if ok, kCodeFileDontSave if file dont save
  ReturnCode Export(const Cave& cave, const std::string& filename) override;
};

}  // namespace mc

#endif  // MAZE_MODEL_CAVE_CAVE_EXPORTER_H_
