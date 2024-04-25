#include <gtest/gtest.h>

#include "cave_test.h"
#include "model/cave/cave.h"

TEST(CaveSetRandom, Common) {
  mc::Cave cave1, cave2, cave3;
  ASSERT_EQ(cave1.SetRandom(3, 5, 7), mc::Cave::ReturnCode::kCodeOk);
  ASSERT_EQ(cave2.SetRandom(35, 42, 7), mc::Cave::ReturnCode::kCodeOk);
  ASSERT_EQ(cave3.SetRandom(99, 1, 1), mc::Cave::ReturnCode::kCodeOk);
}

TEST(CaveSetRandom, ErrChance) {
  mc::Cave cave1, cave2;
  ASSERT_EQ(cave1.SetRandom(-2, 5, 7), mc::Cave::ReturnCode::kCodeInvData);
  ASSERT_EQ(cave2.SetRandom(101, 42, 7), mc::Cave::ReturnCode::kCodeInvData);
}

TEST(CaveSetRandom, ErrSize) {
  mc::Cave cave1, cave2;
  ASSERT_EQ(cave1.SetRandom(35, 52332, 7), mc::Cave::ReturnCode::kCodeInvData);
  ASSERT_EQ(cave2.SetRandom(99, 52, 700), mc::Cave::ReturnCode::kCodeInvData);
}
