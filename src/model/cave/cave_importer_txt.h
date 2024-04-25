// cave importer txt

#ifndef MAZE_CAVE_CAVE_IMPORTER_TXT_H_
#define MAZE_CAVE_CAVE_IMPORTER_TXT_H_

#include <string>

#include "cave.h"
#include "cave_importer.h"

namespace mc {

class CaveImporterTXT : public CaveImporter {
 public:
  using ReturnCode = CaveImporter::ReturnCode;

  CaveImporterTXT();
  virtual ~CaveImporterTXT();

  ReturnCode Import(const std::string& filename, Cave& cave) override;
};

}  // namespace mc

#endif  // MAZE_CAVE_CAVE_IMPORTER_TXT_H_
