#include <gtest/gtest.h>

#include <utility>

#include "cave_test.h"
#include "model/cave/cave.h"

TEST(CaveConstructors, Default) { mc::Cave cave_default; }

TEST(CaveConstructors, Copy) {
  mc::Cave cave;
  mc::Cave::CaveMatrix cavem(5, 5);
  for (mc::Cave::size_type i = 0; i < 5; ++i) {
    for (mc::Cave::size_type j = 0; j < 5; ++j) {
      cavem(i, j) = j;
    }
  }
  cave.SetMatrix(cavem);

  mc::Cave copy_cave(cave);
  ASSERT_TRUE(CaveEq(cave, copy_cave));
}

TEST(CaveConstructors, Move) {
  mc::Cave cave;
  mc::Cave::CaveMatrix cavem(5, 5);
  for (mc::Cave::size_type i = 0; i < 5; ++i) {
    for (mc::Cave::size_type j = 0; j < 5; ++j) {
      cavem(i, j) = j;
    }
  }
  cave.SetMatrix(cavem);

  mc::Cave copy_cave(cave);
  mc::Cave move_cave(std::move(copy_cave));
  ASSERT_TRUE(CaveEq(cave, move_cave));
}

TEST(CaveConstructors, CopyAssign) {
  mc::Cave cave;
  mc::Cave::CaveMatrix cavem(5, 5);
  for (mc::Cave::size_type i = 0; i < 5; ++i) {
    for (mc::Cave::size_type j = 0; j < 5; ++j) {
      cavem(i, j) = j;
    }
  }
  cave.SetMatrix(cavem);

  mc::Cave copy_cave;
  copy_cave = cave;
  ASSERT_TRUE(CaveEq(cave, copy_cave));
}

TEST(CaveConstructors, MoveAssign) {
  mc::Cave cave;
  mc::Cave::CaveMatrix cavem(5, 5);
  for (mc::Cave::size_type i = 0; i < 5; ++i) {
    for (mc::Cave::size_type j = 0; j < 5; ++j) {
      cavem(i, j) = j;
    }
  }
  cave.SetMatrix(cavem);

  mc::Cave copy_cave(cave);
  mc::Cave move_cave;
  move_cave = std::move(copy_cave);
  ASSERT_TRUE(CaveEq(cave, move_cave));
}
