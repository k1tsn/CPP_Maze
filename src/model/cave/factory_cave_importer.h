// factory cave importer

#ifndef MAZE_CAVE_FACTORY_CAVE_IMPORTER
#define MAZE_CAVE_FACTORY_CAVE_IMPORTER

#include "cave_importer.h"

namespace mc {

class FactoryCaveImporter {
 public:
  enum ImportType { kTypeTXT };

  FactoryCaveImporter();
  virtual ~FactoryCaveImporter();

  /// @brief Create new CaveImporter by type
  /// @return New allocated CaveImporter, ownership on memory on you
  virtual CaveImporter* Create(ImportType type);
};

}  // namespace mc

#endif  // MAZE_CAVE_FACTORY_CAVE_IMPORTER
