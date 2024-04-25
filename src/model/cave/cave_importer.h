// interface cave importer

#ifndef MAZE_CAVE_CAVE_IMPORTER_H_
#define MAZE_CAVE_CAVE_IMPORTER_H_

#include <string>

namespace mc {

class Cave;

class CaveImporter {
 public:
  enum ReturnCode { kCodeOk, kCodeFileDontOpen, kCodeInvalidFile };

  CaveImporter() {}
  virtual ~CaveImporter() {}

  virtual ReturnCode Import(const std::string& filename, Cave& cave) = 0;
};

}  // namespace mc

#endif  // MAZE_CAVE_CAVE_IMPORTER_H_
