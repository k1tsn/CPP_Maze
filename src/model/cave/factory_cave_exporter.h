// factory cave exporter

#ifndef MAZE_MODEL_CAVE_FACTORY_CAVE_EXPORTER_H_
#define MAZE_MODEL_CAVE_FACTORY_CAVE_EXPORTER_H_

#include "cave_exporter.h"

namespace mc {

class FactoryCaveExporter {
 public:
  enum ExportType { kTypeTXT };

  FactoryCaveExporter();
  virtual ~FactoryCaveExporter();

  /// @brief Create new CaveExporter by type
  /// @return New allocated CaveExporter, ownership on memory on you
  virtual CaveExporter* Create(ExportType type);
};

}  // namespace mc

#endif  // MAZE_MODEL_CAVE_FACTORY_CAVE_EXPORTER_H_
