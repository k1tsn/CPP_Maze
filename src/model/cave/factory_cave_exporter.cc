// factory cave exporter

#include "factory_cave_exporter.h"

#include "cave_exporter.h"
#include "cave_exporter_txt.h"

namespace mc {

FactoryCaveExporter::FactoryCaveExporter() {}

FactoryCaveExporter::~FactoryCaveExporter() {}

CaveExporter* FactoryCaveExporter::Create(ExportType type) {
  switch (type) {
    case kTypeTXT:
      return new CaveExporterTXT();
      break;

    default:
      break;
  }

  return nullptr;
}

}  // namespace mc
