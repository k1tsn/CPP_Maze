// cave

#include "cave.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

#include "cave_exporter.h"
#include "cave_importer.h"
#include "factory_cave_exporter.h"
#include "factory_cave_importer.h"
#include "matrix.h"

namespace mc {

Cave::Cave() : matrix_(1, 1) { matrix_(0, 0) = true; }

Cave::~Cave() {}

Cave::size_type Cave::GetHeight() const { return matrix_.GetRows(); }

Cave::size_type Cave::GetWidth() const { return matrix_.GetCols(); }

const Cave::CaveMatrix& Cave::GetMatrix() const { return matrix_; }

void Cave::SetMatrix(const CaveMatrix& matrix) { matrix_ = matrix; }

Cave::ReturnCode Cave::Import(const std::string& filename, ImportType type) {
  FactoryCaveImporter factory;
  CaveImporter* cave_importer = factory.Create(type);
  if (cave_importer == nullptr) return kCodeFileDontOpen;

  CaveImporter::ReturnCode im_code = cave_importer->Import(filename, *this);
  ReturnCode code = ImporterCodeConvert(im_code);
  if (code == ReturnCode::kCodeOk &&
      (matrix_.GetCols() > kMaxWidth_ || matrix_.GetRows() > kMaxHeight_))
    code = ReturnCode::kCodeInvalidfile;

  delete cave_importer;
  return code;
}

Cave::ReturnCode Cave::Export(const std::string& filename,
                              ExportType type) const {
  FactoryCaveExporter factory;
  CaveExporter* cave_exporter = factory.Create(type);
  if (cave_exporter == nullptr) return kCodeFileDontSave;

  CaveExporter::ReturnCode ex_code = cave_exporter->Export(*this, filename);
  delete cave_exporter;
  return ExporterCodeConvert(ex_code);
}

Cave::ReturnCode Cave::SetRandom(int chance, size_type w, size_type h) {
  if (chance < 0 || chance > 100) return ReturnCode::kCodeInvData;
  if (w < kMinWidth_ || w > kMaxWidth_) return ReturnCode::kCodeInvData;
  if (h < kMinHeight_ || h > kMaxHeight_) return ReturnCode::kCodeInvData;

  std::srand(std::time(nullptr));
  matrix_ = CaveMatrix(h, w);
  for (size_type i = 0; i < h; ++i) {
    for (size_type j = 0; j < w; ++j) {
      int random_value = std::rand() % 100;
      matrix_(i, j) = (random_value < chance);
    }
  }

  return ReturnCode::kCodeOk;
}

Cave::ReturnCode Cave::NextIteration(int birth_limit, int death_limit) {
  if (birth_limit < kMinBirdthLimit_ || birth_limit > kMaxBirdthLimit_)
    return ReturnCode::kCodeInvData;
  if (death_limit < kMinDeathLimit_ || death_limit > kMaxDeathLimit_)
    return ReturnCode::kCodeInvData;

  CaveMatrix new_matrix(matrix_.GetRows(), matrix_.GetCols());
  for (size_type i = 0; i < matrix_.GetRows(); ++i) {
    for (size_type j = 0; j < matrix_.GetCols(); ++j) {
      int live_count = CountNeigboresLive(i, j);
      if (!IsAlive(i, j) && live_count > birth_limit) {
        new_matrix(i, j) = true;

      } else if (IsAlive(i, j) && live_count < death_limit) {
        new_matrix(i, j) = false;

      } else {
        new_matrix(i, j) = matrix_(i, j);
      }
    }
  }

  if (new_matrix == matrix_) return ReturnCode::kCodeGenerationNotChange;

  matrix_ = new_matrix;
  return ReturnCode::kCodeOk;
}

int Cave::CountNeigboresLive(size_type i, size_type j) const {
  int live_count = 0;

  if (IsAlive(i - 1, j - 1)) ++live_count;
  if (IsAlive(i - 1, j + 0)) ++live_count;
  if (IsAlive(i - 1, j + 1)) ++live_count;
  if (IsAlive(i + 0, j - 1)) ++live_count;
  if (IsAlive(i + 0, j + 1)) ++live_count;
  if (IsAlive(i + 1, j - 1)) ++live_count;
  if (IsAlive(i + 1, j + 0)) ++live_count;
  if (IsAlive(i + 1, j + 1)) ++live_count;

  return live_count;
}

bool Cave::IsAlive(size_type i, size_type j) const {
  if (i >= matrix_.GetRows() || j >= matrix_.GetCols()) return true;

  return matrix_(i, j);
}

Cave::ReturnCode Cave::ImporterCodeConvert(CaveImporter::ReturnCode code) {
  switch (code) {
    case CaveImporter::ReturnCode::kCodeFileDontOpen:
      return ReturnCode::kCodeFileDontOpen;
      break;
    case CaveImporter::ReturnCode::kCodeInvalidFile:
      return ReturnCode::kCodeInvalidfile;
      break;
    default:
      break;
  }
  return ReturnCode::kCodeOk;
}

Cave::ReturnCode Cave::ExporterCodeConvert(CaveExporter::ReturnCode code) {
  switch (code) {
    case CaveExporter::ReturnCode::kCodeFileDontSave:
      return ReturnCode::kCodeFileDontSave;
      break;
    default:
      break;
  }
  return ReturnCode::kCodeOk;
}

const Cave::size_type Cave::kMinWidth_ = 1;
const Cave::size_type Cave::kMaxWidth_ = 50;
const Cave::size_type Cave::kMinHeight_ = 1;
const Cave::size_type Cave::kMaxHeight_ = 50;

const int Cave::kMinBirdthLimit_ = 0;
const int Cave::kMaxBirdthLimit_ = 7;
const int Cave::kMinDeathLimit_ = 0;
const int Cave::kMaxDeathLimit_ = 7;

}  // namespace mc
