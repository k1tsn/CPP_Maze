#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "cave_test.h"
#include "model/cave/cave.h"

using ReturnCode = mc::Cave::ReturnCode;
using ExportType = mc::Cave::ExportType;
using ImportType = mc::Cave::ImportType;

struct CaveExportTestData {
  ExportType export_type_;
  ImportType import_type_;
  ReturnCode code_;
  mc::Cave::size_type width_;
  mc::Cave::size_type height_;
  std::vector<mc::Cave::CaveMatrix::value_type> values_;
};

class CaveExportTest : public ::testing::TestWithParam<int> {
 public:
  static int count_;
  static std::vector<CaveExportTestData> test_data_;
  static std::string kTmpFilename_;
};

std::string CaveExportTest::kTmpFilename_ = ".cave_export_test_tmp.txt";

int CaveExportTest::count_ = 4;
std::vector<CaveExportTestData> CaveExportTest::test_data_ = {
    {ExportType(-2),
     ImportType::kTypeTXT,
     ReturnCode::kCodeFileDontSave,
     0,
     0,
     {}},
    {ExportType::kTypeTXT,
     ImportType::kTypeTXT,
     ReturnCode::kCodeOk,
     10,
     10,
     {
         1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
         0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
         1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
         1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
     }},
    {ExportType::kTypeTXT,
     ImportType::kTypeTXT,
     ReturnCode::kCodeOk,
     1,
     1,
     {1}},
    {ExportType::kTypeTXT,
     ImportType::kTypeTXT,
     ReturnCode::kCodeOk,
     7,
     50,
     {
         1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
         0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0,
         1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
         1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0,
         0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
         1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1,
         0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
         1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1,
         0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1,
         1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1,
         0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1,
         1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
         1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0,
         1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0,
     }},

};

TEST_P(CaveExportTest, Common) {
  int num_test = this->GetParam();
  CaveExportTestData& test_data = CaveExportTest::test_data_[num_test];

  mc::Cave::CaveMatrix mat(test_data.height_, test_data.width_);
  FillMatrix(test_data.values_, mat);
  mc::Cave cave;
  cave.SetMatrix(mat);

  ReturnCode rescode =
      cave.Export(CaveExportTest::kTmpFilename_, test_data.export_type_);
  ASSERT_EQ(rescode, test_data.code_);
  if (rescode != ReturnCode::kCodeOk) return;

  mc::Cave exp_cave;
  exp_cave.Import(CaveExportTest::kTmpFilename_, test_data.import_type_);
  ASSERT_TRUE(CaveEq(cave, exp_cave));
  std::remove(CaveExportTest::kTmpFilename_.c_str());
}

INSTANTIATE_TEST_SUITE_P(My, CaveExportTest,
                         testing::Range(0, CaveExportTest::count_));
