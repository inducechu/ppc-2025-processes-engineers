#include "alekseev_a_min_dist_neigh_elem_vec/seq/include/ops_seq.hpp"

#include <cstdlib>
#include <limits>
#include <tuple>
#include <vector>

#include "alekseev_a_min_dist_neigh_elem_vec/common/include/common.hpp"

namespace alekseev_a_min_dist_neigh_elem_vec {

AlekseevAMinDistNeighElemVecSEQ::AlekseevAMinDistNeighElemVecSEQ(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = std::make_tuple(0, 0);
}

bool AlekseevAMinDistNeighElemVecSEQ::ValidationImpl() {
  return true;
}

bool AlekseevAMinDistNeighElemVecSEQ::PreProcessingImpl() {
  return true;
}

bool AlekseevAMinDistNeighElemVecSEQ::RunImpl() {
  const auto &vec = GetInput();

  int index = 0;
  int index_value = std::numeric_limits<int>::max();
  for (int i = 0; i < static_cast<int>(vec.size()) - 1; i++) {
    int value = std::abs(vec[i] - vec[i + 1]);
    if (value < index_value) {
      index = i;
      index_value = value;
    }
  }

  GetOutput() = std::make_tuple(index, index + 1);
  return true;
}

bool AlekseevAMinDistNeighElemVecSEQ::PostProcessingImpl() {
  return true;
}

}  // namespace alekseev_a_min_dist_neigh_elem_vec
