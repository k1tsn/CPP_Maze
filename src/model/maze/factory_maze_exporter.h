#ifndef MAZE_MODEL_MAZE_FACTORY_MAZE_EXPORTER_TXT_H_
#define MAZE_MODEL_MAZE_FACTORY_MAZE_EXPORTER_TXT_H_

#include "maze_exporter.h"

namespace mc {

class FactoryMazeExporter {
 public:
  enum ExportType { kTypeTXT };
  FactoryMazeExporter();
  virtual ~FactoryMazeExporter();

  /// @brief Create new MazeExporter by type
  /// @return Returns the address of the allocated memory, or nullptr if the
  /// file type is invalid. Dedicated memory requires manual cleanup
  virtual MazeExporter* Create(ExportType type);
};

}  // namespace mc

#endif  // MAZE_MODEL_MAZE_FACTORY_MAZE_EXPORTER_TXT_H_
