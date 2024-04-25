// interface cave exporter

#ifndef MAZE_MODEL_CAVE_CAVE_EXPORTER_H_
#define MAZE_MODEL_CAVE_CAVE_EXPORTER_H_

#include <string>

namespace mc {

class Cave;

class CaveExporter {
 public:
  enum ReturnCode { kCodeOk, kCodeFileDontSave };

  CaveExporter() {}
  virtual ~CaveExporter() {}

  /// @brief Export cave into file
  /// @return kCodeOk if ok, kCodeFileDontSave if file dont save
  virtual ReturnCode Export(const Cave& cave, const std::string& filename) = 0;
};

}  // namespace mc

#endif  // MAZE_MODEL_CAVE_CAVE_EXPORTER_H_
