#include <vector>

#include "model/cave/cave.h"

bool CaveEq(const mc::Cave& a, const mc::Cave& b);

void FillMatrix(const std::vector<mc::Cave::CaveMatrix::value_type>& values,
                mc::Cave::CaveMatrix& m);
