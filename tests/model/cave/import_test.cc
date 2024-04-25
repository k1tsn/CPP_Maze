#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "cave_test.h"
#include "model/cave/cave.h"

using ReturnCode = mc::Cave::ReturnCode;
using ImportType = mc::Cave::ImportType;

struct CaveImportTestData {
  ImportType import_type_;
  ReturnCode code_;
  std::string filename_;
  mc::Cave::size_type width_;
  mc::Cave::size_type height_;
  std::vector<mc::Cave::CaveMatrix::value_type> values_;
};

class CaveImportTest : public ::testing::TestWithParam<int> {
 public:
  static int count_;
  static std::vector<CaveImportTestData> test_data_;
};

int CaveImportTest::count_ = 11;
std::vector<CaveImportTestData> CaveImportTest::test_data_ = {
    {ImportType(-2), ReturnCode::kCodeFileDontOpen, "d", 0, 0, {}},
    {ImportType::kTypeTXT,
     ReturnCode::kCodeInvalidfile,
     "datasets/cave/cave_err_size_51.txt",
     0,
     0,
     {}},
    {ImportType::kTypeTXT,
     ReturnCode::kCodeInvalidfile,
     "datasets/cave/cave_err_size_0.txt",
     0,
     0,
     {}},
    {ImportType::kTypeTXT, ReturnCode::kCodeFileDontOpen, "data", 0, 0, {}},
    {ImportType::kTypeTXT,
     ReturnCode::kCodeInvalidfile,
     "datasets/cave/cave_err_inv_matrix1.txt",
     0,
     0,
     {}},
    {ImportType::kTypeTXT,
     ReturnCode::kCodeInvalidfile,
     "datasets/cave/cave_err_inv_matrix2.txt",
     0,
     0,
     {}},
    {ImportType::kTypeTXT,
     ReturnCode::kCodeInvalidfile,
     "datasets/cave/cave_err_inv_matrix3.txt",
     0,
     0,
     {}},
    {ImportType::kTypeTXT,
     ReturnCode::kCodeInvalidfile,
     "datasets/cave/cave_err_inv_matrix4.txt",
     0,
     0,
     {}},
    {ImportType::kTypeTXT,
     ReturnCode::kCodeOk,
     "datasets/cave/cave1.txt",
     10,
     10,
     {
         1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
         0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
         1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
         1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
     }},
    {ImportType::kTypeTXT,
     ReturnCode::kCodeOk,
     "datasets/cave/cave4.txt",
     1,
     1,
     {1}},
    {ImportType::kTypeTXT,
     ReturnCode::kCodeOk,
     "datasets/cave/cave21.txt",
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

TEST_P(CaveImportTest, Common) {
  int num_test = this->GetParam();
  CaveImportTestData& test_data = CaveImportTest::test_data_[num_test];

  mc::Cave cave;
  ReturnCode rescode = cave.Import(test_data.filename_, test_data.import_type_);
  ASSERT_EQ(rescode, test_data.code_);
  if (rescode != ReturnCode::kCodeOk) return;

  mc::Cave::CaveMatrix exp_mat(test_data.height_, test_data.width_);
  FillMatrix(test_data.values_, exp_mat);
  mc::Cave exp_cave;
  exp_cave.SetMatrix(exp_mat);
  ASSERT_TRUE(CaveEq(cave, exp_cave));
}

INSTANTIATE_TEST_SUITE_P(My, CaveImportTest,
                         testing::Range(0, CaveImportTest::count_));
