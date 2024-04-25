// cave

#ifndef MAZE_MODEL_CAVE_CAVE_H_
#define MAZE_MODEL_CAVE_CAVE_H_

#include <string>

#include "factory_cave_exporter.h"
#include "factory_cave_importer.h"
#include "matrix.h"

namespace mc {

class Cave {
 public:
  enum ReturnCode {
    kCodeOk,
    kCodeFileDontOpen,
    kCodeFileDontSave,
    kCodeInvalidfile,
    kCodeInvData,
    kCodeGenerationNotChange,
  };
  using CaveMatrix = mtlc::Matrix<bool>;
  using size_type = CaveMatrix::size_type;
  using ImportType = FactoryCaveImporter::ImportType;
  using ExportType = FactoryCaveExporter::ExportType;

  Cave();
  Cave(const Cave& other) = default;
  Cave(Cave&& other) noexcept = default;
  Cave& operator=(const Cave& other) = default;
  Cave& operator=(Cave&& other) noexcept = default;
  virtual ~Cave();

  size_type GetHeight() const;
  size_type GetWidth() const;
  const CaveMatrix& GetMatrix() const;

  void SetMatrix(const CaveMatrix& matrix);

  /// @brief Import cave from file
  /// @return kCodeOk if ok
  /// @return kCodeFileDontOpen if file dont open
  /// @return kCodeInvalidfile if file invalid
  ReturnCode Import(const std::string& filename, ImportType type);

  /// @brief Export cave to file
  /// @return kCodeOk if ok
  /// @return kCodeFileDontSave if file dont save
  ReturnCode Export(const std::string& filename, ExportType type) const;

  /// @brief Set random values cave
  /// @param chance chance to cell will live
  /// @param w cave width
  /// @param h cave height
  /// @return kCodeOk if ok.
  /// @return kCodeInvData if chance not in [0, 100] or w not in [1, 50] or h
  /// not in [1, 50].
  ReturnCode SetRandom(int chance, size_type w, size_type h);

  /// @brief Next iteration cell automat
  /// @return kCodeOk if ok.
  /// @return kCodeInvData if limits not in range [0, 7].
  /// @return kCodeGenerationNotChange if cave dont change
  ReturnCode NextIteration(int birth_limit, int death_limit);

 private:
  int CountNeigboresLive(size_type i, size_type j) const;
  bool IsAlive(size_type i, size_type j) const;

  static ReturnCode ImporterCodeConvert(CaveImporter::ReturnCode code);
  static ReturnCode ExporterCodeConvert(CaveExporter::ReturnCode code);

  static const size_type kMinWidth_;
  static const size_type kMaxWidth_;
  static const size_type kMinHeight_;
  static const size_type kMaxHeight_;

  static const int kMinBirdthLimit_;
  static const int kMaxBirdthLimit_;
  static const int kMinDeathLimit_;
  static const int kMaxDeathLimit_;

  CaveMatrix matrix_;
};

}  // namespace mc

#endif  // MAZE_MODEL_CAVE_CAVE_H_
