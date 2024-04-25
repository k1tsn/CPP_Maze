#include <gtest/gtest.h>

#include <vector>

#include "cave_test.h"
#include "model/cave/cave.h"

using ReturnCode = mc::Cave::ReturnCode;

struct CaveNextIterationTestData {
  ReturnCode code_;
  int birdt_limit_;
  int death_limit;
  mc::Cave::size_type width_;
  mc::Cave::size_type height_;
  std::vector<mc::Cave::CaveMatrix::value_type> values_;
  std::vector<mc::Cave::CaveMatrix::value_type> res_values_;
};

class CaveNextIterationTest : public ::testing::TestWithParam<int> {
 public:
  static int count_;
  static std::vector<CaveNextIterationTestData> test_data_;
};

int CaveNextIterationTest::count_ = 8;
std::vector<CaveNextIterationTestData> CaveNextIterationTest::test_data_ = {
    {ReturnCode::kCodeInvData, -3, 4, 1, 1, {1}, {1}},
    {ReturnCode::kCodeInvData, 9, 4, 1, 1, {1}, {1}},
    {ReturnCode::kCodeInvData, 3, -1, 1, 1, {1}, {1}},
    {ReturnCode::kCodeInvData, 3, 445, 1, 1, {1}, {1}},

    {ReturnCode::kCodeOk,
     4,
     4,
     10,
     10,
     {
         1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
         0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
         1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
         1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
     },
     {
         1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1,
         0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
         1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
     }},

    {ReturnCode::kCodeOk,
     0,
     0,
     10,
     10,
     {
         1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
         0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
         1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
         1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
     },
     {
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     }},

    {ReturnCode::kCodeOk,
     7,
     7,
     10,
     10,
     {
         1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
         0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
         1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
         1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
     },
     {
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     }},

    {ReturnCode::kCodeGenerationNotChange,
     5,
     4,
     5,
     5,
     {
         1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0,
         1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
     },
     {
         1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0,
         1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
     }},
};

TEST_P(CaveNextIterationTest, Common) {
  int num_test = this->GetParam();
  CaveNextIterationTestData& test_data =
      CaveNextIterationTest::test_data_[num_test];

  mc::Cave::CaveMatrix m(test_data.height_, test_data.width_);
  mc::Cave::CaveMatrix res_m(test_data.height_, test_data.width_);
  FillMatrix(test_data.values_, m);
  FillMatrix(test_data.res_values_, res_m);

  mc::Cave cave, res_cave;
  cave.SetMatrix(m);
  res_cave.SetMatrix(res_m);

  ReturnCode rescode =
      cave.NextIteration(test_data.birdt_limit_, test_data.death_limit);
  ASSERT_EQ(rescode, test_data.code_);
  if (rescode != ReturnCode::kCodeOk) return;

  ASSERT_TRUE(CaveEq(cave, res_cave));
}

INSTANTIATE_TEST_SUITE_P(My, CaveNextIterationTest,
                         testing::Range(0, CaveNextIterationTest::count_));
