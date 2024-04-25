// factory cave importer

#include "factory_cave_importer.h"

#include "cave_importer.h"
#include "cave_importer_txt.h"

namespace mc {

FactoryCaveImporter::FactoryCaveImporter() {}

FactoryCaveImporter::~FactoryCaveImporter() {}

CaveImporter* FactoryCaveImporter::Create(ImportType type) {
  switch (type) {
    case kTypeTXT:
      return new CaveImporterTXT();
      break;

    default:
      break;
  }

  return nullptr;
}

}  // namespace mc
