#include "factory_maze_exporter.h"

#include "maze_exporter.h"
#include "maze_exporter_txt.h"

namespace mc {

FactoryMazeExporter::FactoryMazeExporter() {}

FactoryMazeExporter::~FactoryMazeExporter() {}

MazeExporter* FactoryMazeExporter::Create(ExportType type) {
  switch (type) {
    case ExportType::kTypeTXT:
      return new MazeExporterTXT();
      break;

    default:
      break;
  }

  return nullptr;
}

}  // namespace mc
