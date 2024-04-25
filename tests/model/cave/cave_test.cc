#include "model/cave/cave.h"

#include <vector>

#include "cave_test.h"

bool CaveEq(const mc::Cave& a, const mc::Cave& b) {
  if (a.GetHeight() != b.GetHeight()) return false;
  if (a.GetWidth() != b.GetWidth()) return false;
  if (a.GetMatrix() != b.GetMatrix()) return false;
  return true;
}

void FillMatrix(const std::vector<mc::Cave::CaveMatrix::value_type>& values,
                mc::Cave::CaveMatrix& m) {
  std::vector<mc::Cave::CaveMatrix::value_type>::size_type vi = 0;
  for (mc::Cave::CaveMatrix::size_type i = 0; i < m.GetRows(); ++i) {
    for (mc::Cave::CaveMatrix::size_type j = 0; j < m.GetCols(); ++j) {
      m(i, j) = values[vi];
      ++vi;
    }
  }
}