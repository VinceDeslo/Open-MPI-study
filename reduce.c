#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

  int result, count = 1;
  int root = 0;
  int nb_proc, rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Sum up the ranks of all processes
  MPI_Reduce(&rank, &result, count, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root)
    printf("[MPI rank %d] Sum of ranks: %d\n", rank, result);

  MPI_Finalize();
  
  return EXIT_SUCCESS;
}