#ifndef MAZE_MODEL_MAZE_FACTORY_MAZE_IMPORTER_TXT_H_
#define MAZE_MODEL_MAZE_FACTORY_MAZE_IMPORTER_TXT_H_

#include "maze_importer.h"

namespace mc {

class FactoryMazeImporter {
 public:
  enum ImportType { kTypeTXT };
  FactoryMazeImporter();
  virtual ~FactoryMazeImporter();

  /// @brief Create new MazeExporter by type
  /// @return Returns the address of the allocated memory, or nullptr if the
  /// file type is invalid. Dedicated memory requires manual cleanup
  virtual MazeImporter* Create(ImportType type);
};

}  // namespace mc

#endif  // MAZE_MODEL_MAZE_FACTORY_MAZE_IMPORTER_TXT_H_
