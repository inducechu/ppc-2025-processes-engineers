#include "alekseev_a_min_dist_neigh_elem_vec/mpi/include/ops_mpi.hpp"

#include <mpi.h>

#include <cstdlib>
#include <limits>
#include <tuple>
#include <vector>

#include "alekseev_a_min_dist_neigh_elem_vec/common/include/common.hpp"

namespace alekseev_a_min_dist_neigh_elem_vec {

AlekseevAMinDistNeighElemVecMPI::AlekseevAMinDistNeighElemVecMPI(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = std::make_tuple(0, 0);
}

bool AlekseevAMinDistNeighElemVecMPI::ValidationImpl() {
  return true;
}

bool AlekseevAMinDistNeighElemVecMPI::PreProcessingImpl() {
  return true;
}

bool AlekseevAMinDistNeighElemVecMPI::RunImpl() {
  int rank = 0;
  int comm_size = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  const auto &vec = GetInput();


  int local_index = rank;
  int local_dist = std::numeric_limits<int>::max();

  for(int i = rank; i < static_cast<int>(vec.size()) - 1; i += comm_size){
    int value = std::abs(vec[i] - vec[i + 1]);
    if(local_dist > value){
      local_dist = value;
      local_index = i;
    }
  }

  int global_dist = std::numeric_limits<int>::max();
  int global_index = static_cast<int>(GetInput().size());
  MPI_Allreduce(&local_dist, &global_dist, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

  int finish_global_index = std::numeric_limits<int>::max();

  if (local_dist == global_dist) {
    global_index = local_index;
  }
  MPI_Allreduce(&global_index, &finish_global_index, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

  GetOutput() = std::make_tuple(finish_global_index, finish_global_index + 1);
  return true;
}

bool AlekseevAMinDistNeighElemVecMPI::PostProcessingImpl() {
  return true;
}

} // namespace alekseev_a_min_dist_neigh_elem_vec
