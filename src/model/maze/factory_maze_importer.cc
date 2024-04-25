#include "factory_maze_importer.h"

#include "maze_importer.h"
#include "maze_importer_txt.h"

namespace mc {

FactoryMazeImporter::FactoryMazeImporter() {}

FactoryMazeImporter::~FactoryMazeImporter() {}

MazeImporter* FactoryMazeImporter::Create(ImportType type) {
  switch (type) {
    case ImportType::kTypeTXT:
      return new MazeImporterTXT();
      break;

    default:
      break;
  }

  return nullptr;
}

}  // namespace mc
